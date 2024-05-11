#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_b, int* dev_c);

cudaError_t multiplyWithCuda(int* c, const int* a, const int* b, unsigned int size);

void printMatrix(int* matrix, int size);




__global__ void multiplyKernel(int* c, int* a, int* b, unsigned int size)
{
	// BLOCK_SIZE^2 должно давать макс число потоков в блоке
	const int BLOCK_SIZE = 16;

	// индекс для выходной матрицы
	int index = blockIdx.y * blockDim.x * blockDim.y * gridDim.x + blockIdx.x * blockDim.y + threadIdx.y * blockDim.x * gridDim.x + threadIdx.x;
	
	// адрес выходного элемента, если представлять массив c в виде матрицы
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;

	// смещение, если размерность матрицы не кратна BLOCK_SIZE
	index -= (blockDim.x * gridDim.x - size) * j;

	int sum = 0;
	__shared__ int a_buff[BLOCK_SIZE][BLOCK_SIZE];
	__shared__ int b_buff[BLOCK_SIZE][BLOCK_SIZE];
	for (size_t k = 0, bx = 0, by = 0;  k < BLOCK_SIZE * BLOCK_SIZE; k+=BLOCK_SIZE, bx++, by++)
	{
		// индексы элементов в подматрицах, в конце вычитание - смещение аналогичное переменной index
		int a_index = blockIdx.y * blockDim.x * blockDim.y * gridDim.x + bx * blockDim.y + threadIdx.y * blockDim.x * gridDim.x + threadIdx.x - (blockDim.x * gridDim.x - size) * j;
		int b_index = by * blockDim.x * blockDim.y * gridDim.x + blockIdx.x * blockDim.y + threadIdx.y * blockDim.x * gridDim.x + threadIdx.x - (blockDim.x * gridDim.x - size) * (by * blockDim.y + threadIdx.y);
		
		// контроль выхода за пределы размеров матрицы (если больше необходимого заполняем 0, так как не влияет на конечный результат)
		if (a_index >= size * (j + 1)) {
			a_buff[threadIdx.y][threadIdx.x] = 0;
		}
		else {
			a_buff[threadIdx.y][threadIdx.x] = a[a_index];
		}

		if (b_index >= size * (by * blockDim.y + threadIdx.y + 1)) {
			b_buff[threadIdx.y][threadIdx.x] = 0;
		}
		else {
			b_buff[threadIdx.y][threadIdx.x] = b[b_index];
		}

		__syncthreads();
		for (int k = 0; k < BLOCK_SIZE; k++)
		{
			sum += a_buff[threadIdx.y][k] * b_buff[k][threadIdx.x];
		}
		__syncthreads();
	}

	// контроль выхода за пределы размеров матрицы
	if (i >= size || j >= size)
		return;
	c[index] = sum;
}


int main()
{
	// вариант 0
	printf("Variant 0\n");
	int arraySize;
	scanf("%d", &arraySize);
	int* a = (int*)malloc(arraySize * arraySize * sizeof(int));
	int* b = (int*)malloc(arraySize * arraySize * sizeof(int));
	int* c = (int*)malloc(arraySize * arraySize * sizeof(int));
	for (size_t i = 0; i < arraySize; i++)
	{
		for (size_t j = 0; j < arraySize; j++)
		{
			a[i * arraySize + j] = rand() % 100 + 1;
			b[i * arraySize + j] = rand() % 100 + 1;
			c[i * arraySize + j] = 0;
		}
	}


	// Add vectors in parallel.
	cudaError_t cudaStatus = multiplyWithCuda(c, a, b, arraySize);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "addWithCuda failed!");
		return 1;
	}

	// cudaDeviceReset must be called before exiting in order for profiling and
	// tracing tools such as Nsight and Visual Profiler to show complete traces.
	cudaStatus = cudaDeviceReset();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceReset failed!");
		return 1;
	}

	/*printf("A:\n");
	printMatrix(a, arraySize);
	printf("B:\n");
	printMatrix(b, arraySize);
	printf("C:\n");
	printMatrix(c, arraySize);*/


	return 0;
}

// Helper function for using CUDA to add vectors in parallel.
cudaError_t multiplyWithCuda(int* c, const int* a, const int* b, unsigned int size)
{
	cudaDeviceProp	devProp;
	cudaGetDeviceProperties(&devProp, 0);
	int* dev_a = 0;
	int* dev_b = 0;
	int* dev_c = 0;
	cudaError_t cudaStatus;

	int dev_size = size * size;

	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaStatus = cudaSetDevice(0);
	checkError(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?", dev_a, dev_b, dev_c);

	// Allocate GPU buffers for three vectors (two input, one output)    .
	cudaStatus = cudaMalloc((void**)&dev_c, dev_size * sizeof(int));
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_b, dev_c);

	cudaStatus = cudaMalloc((void**)&dev_a, dev_size * sizeof(int));
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_b, dev_c);

	cudaStatus = cudaMalloc((void**)&dev_b, dev_size * sizeof(int));
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_b, dev_c);

	// Copy input vectors from host memory to GPU buffers.
	cudaStatus = cudaMemcpy(dev_a, a, dev_size * sizeof(int), cudaMemcpyHostToDevice);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_b, dev_c);

	cudaStatus = cudaMemcpy(dev_b, b, dev_size * sizeof(int), cudaMemcpyHostToDevice);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_b, dev_c);

	cudaStatus = cudaMemcpy(dev_c, c, dev_size * sizeof(int), cudaMemcpyHostToDevice);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_b, dev_c);

	// Launch a kernel on the GPU with one thread for each element.
	cudaEvent_t start, stop;		//описываем переменные типа  cudaEvent_t 
	float       gpuTime = 0.0f;
	// создаем события начала и окончания выполнения ядра 
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	//привязываем событие start  к данному месту 
	cudaEventRecord(start, 0);

	double d;
	if (size < sqrt(devProp.maxThreadsPerBlock)) {
		d = size;
	}
	else {
		d = sqrt(devProp.maxThreadsPerBlock);
	}
	d = 16;
	dim3 threads(d, d, 1);
	dim3 blocks(ceil(size / d), ceil(size / d), 1);
	multiplyKernel << <blocks, threads >> > (dev_c, dev_a, dev_b, size);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	checkError(cudaStatus, "multiplyKernel launch failed: %s\n", dev_a, dev_b, dev_c);

	// cudaDeviceSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	checkError(cudaStatus, "cudaDeviceSynchronize returned error code %d after launching multiplyKernel!\n", dev_a, dev_b, dev_c);

	cudaEventRecord(stop, 0);

	cudaEventSynchronize(stop);
	// запрашиваем время между событиями 
	cudaEventElapsedTime(&gpuTime, start, stop);
	printf("time spent executing by the GPU: %.5f ms\n", gpuTime);
	// уничтожаем созданные события 
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	// Copy output vector from GPU buffer to host memory.
	cudaStatus = cudaMemcpy(c, dev_c, dev_size * sizeof(int), cudaMemcpyDeviceToHost);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_b, dev_c);

	return cudaStatus;
}


void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_b, int* dev_c)
{
	if (cudaStatus == cudaSuccess)
		return;

	printf(msg);
	printf(cudaGetErrorString(cudaStatus));
	cudaFree(dev_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
}

void printMatrix(int* matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", matrix[i * size + j]);
		printf("\n");
	}
	printf("\n");
}