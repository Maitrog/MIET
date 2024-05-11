#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define VAR  0;

void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_b, int* dev_c);

cudaError_t multiplyWithCuda(int* c, const int* a, const int* b, unsigned int size);

void printMatrix(int* matrix, int size);

void printArray(int* a, int size);



// вариант 1
#if VAR == 1

__global__ void multiplyKernel(int* c, const int* a, const int* b)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	c[i] = a[i] * b[i];
}

#else

__global__ void multiplyKernel(int* c, int* a, int* b, unsigned int size)
{
	int index = blockIdx.y * blockDim.x * blockDim.y * gridDim.x + blockIdx.x * blockDim.y + threadIdx.y * blockDim.x * gridDim.x + threadIdx.x;
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;
	index -= (blockDim.x * gridDim.x - size) * j;
	if (i >= size || j >= size)
		return;

	for (size_t k = 0; k < size; k++)
	{
		c[index] += a[j * size + k] * b[k * size + i];
	}
}

#endif

int main()
{
	// вариант 1
#if VAR == 1
	printf("Variant 1\n");
	printf("Enter array size: ");
	int arraySize;
	scanf("%d", &arraySize);
	int* a = (int*)malloc(arraySize * sizeof(int));
	int* b = (int*)malloc(arraySize * sizeof(int));
	int* c = (int*)malloc(arraySize * sizeof(int));
	for (size_t i = 0; i < arraySize; i++)
	{
		a[i] = rand() % 100 + 1;
		b[i] = rand() % 100 + 1;
		c[i] = 0;
	}

#else

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

#endif

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

#if VAR == 1

	printf("A: ");
	printArray(a, arraySize);

	printf("\nB: ");
	printArray(b, arraySize);

	printf("\nC: ");
	int sum = 0;
	for (int i = 0; i < arraySize; i++) {
		sum += c[i];
	}
	printf("%d", sum);

#else

	/*printf("A:\n");
	printMatrix(a, arraySize);
	printf("B:\n");
	printMatrix(b, arraySize);
	printf("C:\n");
	printMatrix(c, arraySize);*/
	for (int i = 0; i < arraySize; i++)
		for (int j = 0; j < arraySize; j++)
		{
			int test = 0;
			for (int k = 0; k < arraySize; k++)
				test += a[i * arraySize + k] * b[k * arraySize + j];
			if (test != c[i * arraySize + j]) {
				printf("wrong answer");
			}
		}

#endif

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

#if VAR == 1
	int dev_size = size;
#else
	int dev_size = size * size;
#endif

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
#if VAR == 1
	
	dim3 threads;
	if (dev_size < devProp.maxThreadsPerBlock) {
		threads = dim3(dev_size, 1, 1);
	}
	else {
		threads = dim3(devProp.maxThreadsPerBlock, 1, 1);
	}
	dim3 blocks(ceil(dev_size / threads.x), 1, 1);
	multiplyKernel << <blocks, threads >> > (dev_c, dev_a, dev_b);
#else
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

#endif

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
	cudaFree(dev_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
}

void printArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", a[i]);
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