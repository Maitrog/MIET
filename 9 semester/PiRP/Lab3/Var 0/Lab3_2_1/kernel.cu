
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <crt/math_functions.hpp>


void printArray(int* a, int size);

void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_c);

void validate(int result, int* array, int arraySize);

cudaError_t reductionMinWithCuda(int* c, const int* a, unsigned int size, int threadSize, int blockSize, void(*kernel) (dim3, dim3, int, int*, int*, int));

__global__ void reductionMin4(int* inData, int* outData, int arraySize)
{
	extern __shared__ int data[];
	int tid = threadIdx.x;
	int i = 2 * blockIdx.x * blockDim.x + threadIdx.x;
	if (i + blockDim.x < arraySize) {
		data[tid] = min(inData[i], inData[i + blockDim.x]);
	}
	else {
		data[tid] = inData[i];
	}
	__syncthreads();
	for (int s = blockDim.x / 2; s > 0; s >>= 1)
	{
		if (tid < s)
		{
			int v = min(data[tid], data[tid + s]);
			data[tid] = v;
		}
		__syncthreads();
	}
	if (tid == 0)
		outData[blockIdx.x] = data[0];
}

__global__ void reductionMin1(int* inData, int* outData, int arraySize)
{
	extern __shared__ int data[];
	int tid = threadIdx.x;
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i >= arraySize)
		data[i] = INT_MAX;
	else
		data[tid] = inData[i]; 	// load into shared memory 
	__syncthreads();

	for (int s = 1; s < blockDim.x; s *= 2) {
		if (tid % (2 * s) == 0) 	// heavy branching !!! 
			data[tid] = min(data[tid], data[tid + s]);
		__syncthreads();
	}
	if (tid == 0)
		outData[blockIdx.x] = data[0];
}


__global__ void reductionMin2(int* inData, int* outData, int arraySize)
{
	extern __shared__ int data[];
	int tid = threadIdx.x;
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i >= arraySize)
		return;

	data[tid] = inData[i]; 	// load into shared memory 
	__syncthreads();
	for (int s = 1; s < blockDim.x; s <<= 1)
	{
		int index = 2 * s * tid;
		if (index < blockDim.x)
			data[index] = min(data[index], data[index + s]);
		__syncthreads();
	}
	if (tid == 0) 		// write result of block reduction 
		outData[blockIdx.x] = data[0];
}

__global__ void reductionMin3(int* inData, int* outData, int arraySize)
{
	extern __shared__ int data[];
	int tid = threadIdx.x;
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i >= arraySize)
		return;

	data[tid] = inData[i];
	__syncthreads();
	for (int s = blockDim.x / 2; s > 0; s >>= 1)
	{
		if (tid < s)
			data[tid] = min(data[tid], data[tid + s]);
		__syncthreads();
	}
	if (tid == 0)
		outData[blockIdx.x] = data[0];
}

void reductionMin1withCuda(dim3 blocks, dim3 threads, int threadSize, int* dev_a, int* dev_c, int size) {
	reductionMin1<<<blocks, threads, threadSize * sizeof(int)>>>(dev_a, dev_c, size);
}

void reductionMin2withCuda(dim3 blocks, dim3 threads, int threadSize, int* dev_a, int* dev_c, int size) {
	reductionMin2 << <blocks, threads, threadSize * sizeof(int) >> > (dev_a, dev_c, size);
}

void reductionMin3withCuda(dim3 blocks, dim3 threads, int threadSize, int* dev_a, int* dev_c, int size) {
	reductionMin3 << <blocks, threads, threadSize * sizeof(int) >> > (dev_a, dev_c, size);
}

void reductionMin4withCuda(dim3 blocks, dim3 threads, int threadSize, int* dev_a, int* dev_c, int size) {
	reductionMin4 << <blocks, threads, threadSize * sizeof(int) >> > (dev_a, dev_c, size);
}

int main()
{
	printf("Enter array size: ");
	int arraySize;
	scanf("%d", &arraySize);
	int threadSize = 256;
	int blockSize = ceil(arraySize / threadSize);
	int blockSize2 = ceil(arraySize / threadSize / 2);
	int* a = (int*)malloc(arraySize * sizeof(int));
	int* c = (int*)malloc(blockSize * sizeof(int));
	for (size_t i = 0; i < arraySize; i++)
	{
		a[i] = rand() * (rand() % 2 == 0 ? -1 : 1);
	}

	cudaError_t cudaStatus = reductionMinWithCuda(c, a, arraySize, threadSize, blockSize, reductionMin1withCuda);
	validate(c[0], a, arraySize);
	c = (int*)malloc(blockSize * sizeof(int));
	
	cudaStatus = reductionMinWithCuda(c, a, arraySize, threadSize, blockSize, reductionMin2withCuda);
	validate(c[0], a, arraySize);
	c = (int*)malloc(blockSize * sizeof(int));

	cudaStatus = reductionMinWithCuda(c, a, arraySize, threadSize, blockSize, reductionMin3withCuda);
	validate(c[0], a, arraySize);
	c = (int*)malloc(blockSize * sizeof(int));

	cudaStatus = reductionMinWithCuda(c, a, arraySize, threadSize, blockSize2, reductionMin4withCuda);
	validate(c[0], a, arraySize);

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

	return 0;
}

// Helper function for using CUDA to add vectors in parallel.
cudaError_t reductionMinWithCuda(int* c, const int* a, unsigned int size, int threadSize, int blockSize, void(*kernel) (dim3, dim3, int, int*, int*, int))
{
	cudaDeviceProp	devProp;
	cudaGetDeviceProperties(&devProp, 0);
	int* dev_a = 0;
	int* dev_c = 0;
	cudaError_t cudaStatus;

	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaStatus = cudaSetDevice(0);
	checkError(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?", dev_a, dev_c);

	cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_c);

	cudaStatus = cudaMalloc((void**)&dev_c, blockSize * sizeof(int));
	checkError(cudaStatus, "cudaMemcpy failed!", dev_c, dev_c);

	cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_c);

	// Launch a kernel on the GPU with one thread for each element.
	cudaEvent_t start, stop;		//описываем переменные типа  cudaEvent_t 
	float       gpuTime = 0.0f;
	// создаем события начала и окончания выполнения ядра 
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	//привязываем событие start  к данному месту 
	cudaEventRecord(start, 0);

	dim3 threads(threadSize, 1, 1);
	dim3 blocks(blockSize, 1, 1);
	kernel(blocks, threads, threadSize, dev_a, dev_c, size);
	//reductionMin1 << <blocks, threads, threadSize * sizeof(int) >> > (dev_a, dev_c, size);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	checkError(cudaStatus, "reductionMin4 launch failed: %s\n", dev_a, dev_c);

	// cudaDeviceSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	checkError(cudaStatus, "cudaDeviceSynchronize returned error code %d after launching reductionMin4!\n", dev_a, dev_c);

	cudaEventRecord(stop, 0);

	cudaEventSynchronize(stop);
	// запрашиваем время между событиями 
	cudaEventElapsedTime(&gpuTime, start, stop);
	printf("time spent executing by the GPU: %.5f ms\n", gpuTime);
	// уничтожаем созданные события 
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	// Copy output vector from GPU buffer to host memory.
	cudaStatus = cudaMemcpy(c, dev_c, blockSize * sizeof(int), cudaMemcpyDeviceToHost);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_c);

	for (size_t i = 1; i < blockSize; i++)
	{
		if (c[i] < c[0]) {
			c[0] = c[i];
		}
	}

	return cudaStatus;
}


void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_c)
{
	if (cudaStatus == cudaSuccess)
		return;

	printf(msg);
	cudaFree(dev_a);
	cudaFree(dev_c);
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

void validate(int result, int* array, int arraySize) {
	int v = array[0];
	for (size_t i = 0; i < arraySize; i++)
	{
		if (array[i] < v) {
			v = array[i];
		}
	}
	if (result != v) {
		printf("\nWrong answer. Real answear %d\n", v);
	}
	else {
		printf("\nAnswer success\n");
	}
}