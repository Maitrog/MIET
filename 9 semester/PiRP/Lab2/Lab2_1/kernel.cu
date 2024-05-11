#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_b, int* dev_c);

cudaError_t multiplyWithCuda(int* c, const int* a, const int* b, unsigned int size);

void printArray(int* a, int size);

__global__ void multiplyKernel(int* c, const int* a, const int* b)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (threadIdx.x == 30) {
		i+=10;
	}
	c[i] = a[i] + b[i];

}

int main()
{
	// вариант 1
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


	//printf("A: ");
	//printArray(a, arraySize);

	//printf("\nB: ");
	//printArray(b, arraySize);

	//printf("\nC: ");
	//int sum = 0;
	//for (int i = 0; i < arraySize; i++) {
	//	sum += c[i];
	//}
	//printf("%d", sum);


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

	int dev_size = size;

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

	//for (int offset = 0; offset < 128; offset++) {
		// Launch a kernel on the GPU with one thread for each element.
		cudaEvent_t start, stop;		//описываем переменные типа  cudaEvent_t 
		float       gpuTime = 0.0f;
		// создаем события начала и окончания выполнения ядра 
		cudaEventCreate(&start);
		cudaEventCreate(&stop);
		//привязываем событие start  к данному месту 
		cudaEventRecord(start, 0);

		dim3 threads;
		if (dev_size < devProp.maxThreadsPerBlock) {
			threads = dim3(dev_size, 1, 1);
		}
		else {
			threads = dim3(devProp.maxThreadsPerBlock, 1, 1);
		}
		dev_size = 32;
		threads = dim3(32, 1, 1);
		dim3 blocks(ceil(dev_size / threads.x), 1, 1);
		multiplyKernel << <blocks, threads >> > (dev_c, dev_a, dev_b);

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
	//}
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

void printArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", a[i]);
}