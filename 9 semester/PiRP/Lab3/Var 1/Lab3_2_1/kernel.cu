
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <crt/math_functions.hpp>


void printArray(int* a, int size);

void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_c);

void validate(int* result, int* array, int arraySize);

void prefixSumKernel(int* inData, int* outData, int& arraySize, int& blockSize, int sharedSize, void(*prefixSum) (int* inData, int* outData, int* sums, int arraySize));

void prefixSumKernel1(int* inData, int* outData, int& arraySize, int& blockSize);

void prefixSumKernel2(int* inData, int* outData, int& arraySize, int& blockSize);

cudaError_t prefixSumWithCuda(int* c, const int* a, int size, int threadsCount, void (*prefixSumKernel) (int* inData, int* outData, int& arraySize, int& blockSize));

__global__ void prefixSum1(int* inData, int* outData, int* sums, int arraySize)
{
	extern __shared__ int temp[];
	int id = 2 * blockDim.x * blockIdx.x + threadIdx.x;
	int tid = threadIdx.x;
	int offset = 1;
	int BLOCK_SIZE = blockDim.x;
	int sharedSize = 2 * BLOCK_SIZE;
	
	temp[tid] = inData[id]; // load into shared memory
	temp[tid + BLOCK_SIZE] = inData[id + BLOCK_SIZE];

	for (int d = sharedSize >> 1; d > 0; d >>= 1) {
		__syncthreads();
		if (tid < d)
		{
			int ai = offset * (2 * tid + 1) - 1;
			int bi = offset * (2 * tid + 2) - 1;
			temp[bi] += temp[ai];
		}
		offset <<= 1;
	}
	if (tid == 0) {
		sums[blockIdx.x] = temp[sharedSize - 1];
		temp[sharedSize - 1] = 0; // clear the last element 
	}
	for (int d = 1; d < sharedSize; d <<= 1)
	{
		offset >>= 1;
		__syncthreads();
		if (tid < d)
		{
			int ai = offset * (2 * tid + 1) - 1;
			int bi = offset * (2 * tid + 2) - 1;
			int t = temp[ai];
			temp[ai] = temp[bi];
			temp[bi] += t;
		}
	}
	__syncthreads();
	outData[2 * blockDim.x * blockIdx.x + 2 * tid] = temp[2 * tid]; // write results 
	outData[2 * blockDim.x * blockIdx.x + 2 * tid + 1] = temp[2 * tid + 1];
}

__global__ void prefixSum2(int* inData, int* outData, int* sums, int arraySize)
{
	extern __shared__ int temp[];
	int BLOCK_SIZE = blockDim.x * blockDim.y * blockDim.z;
	int tid = threadIdx.x;
	int offset = 1;
	int ai = tid; // 0 -> 255
	int bi = tid + (arraySize / 2); // 256 -> 511
	int offsA = (ai >> 4); // from 0 to 15
	int offsB = (bi >> 4); // from 16 to 31
	temp[ai + offsA] = inData[ai + 2 * BLOCK_SIZE * blockIdx.x];
	temp[bi + offsB] = inData[bi + 2 * BLOCK_SIZE * blockIdx.x];
	for (int d = arraySize >> 1; d > 0; d >>= 1, offset <<= 1)
	{
		__syncthreads();
		if (tid < d)
		{
			int ai = offset * (2 * tid + 1) - 1;
			int bi = offset * (2 * tid + 2) - 1;
			ai += ai >> 4;
			bi += bi >> 4;
			temp[bi] += temp[ai];
		}
	}
	if (tid == 0)
	{
		int i = arraySize - 1 + ((arraySize - 1) >> 4);  // для scan больших массивов
		sums[blockIdx.x] = temp[i];             // для scan больших массивов
		temp[i] = 0; // clear the last element 
	}
	for (int d = 1; d < arraySize; d <<= 1)
	{
		offset >>= 1;
		__syncthreads();
		if (tid < d)
		{
			int ai = offset * (2 * tid + 1) - 1;
			int bi = offset * (2 * tid + 2) - 1;
			int t;
			ai += (ai >> 4);
			bi += (bi >> 4);
			t = temp[ai];
			temp[ai] = temp[bi];
			temp[bi] += t;
		}
	}
	__syncthreads();
	outData[ai + 2 * BLOCK_SIZE * blockIdx.x] = temp[ai + offsA];
	outData[bi + 2 * BLOCK_SIZE * blockIdx.x] = temp[bi + offsB];
}

__global__ void finalPrefixSum(int* data, int* sums, int arraySize, int blockSize)
{
	int index = threadIdx.x + blockIdx.x * 2 * blockSize;
	if (index <= arraySize) {
		int v = data[index] + sums[blockIdx.x];
		data[index] = v;
	}
}


int main()
{
	printf("Enter array size: ");
	int arraySize;
	scanf("%d", &arraySize);
	int threadsCount = 64; // больше ставить не рекомендую, перестает работать стабильно работать, хз почему
	int* a = (int*)malloc(arraySize * sizeof(int));
	int* c = (int*)malloc(arraySize * sizeof(int));

	for (size_t i = 0; i < arraySize; i++)
	{
		a[i] = rand() * (rand() % 2 == 0 ? -1 : 1);
	}

	cudaError_t cudaStatus = prefixSumWithCuda(c, a, arraySize, threadsCount, prefixSumKernel1);
	validate(c, a, arraySize);
	c = (int*)malloc(arraySize * sizeof(int));

	cudaStatus = prefixSumWithCuda(c, a, arraySize, threadsCount, prefixSumKernel1);
	validate(c, a, arraySize);
	c = (int*)malloc(arraySize * sizeof(int));

	cudaStatus = prefixSumWithCuda(c, a, arraySize, threadsCount, prefixSumKernel2);
	validate(c, a, arraySize);

	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "prefixSumWithCuda failed!");
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

cudaError_t prefixSumWithCuda(int* c, const int* a, int size, int threadsCount, void (*prefixSumKernel) (int* inData, int* outData, int& arraySize, int& blockSize))
{
	cudaDeviceProp	devProp;
	cudaGetDeviceProperties(&devProp, 0);
	int* dev_a = 0;
	int* dev_c = 0;
	cudaError_t cudaStatus;

	cudaStatus = cudaSetDevice(0);
	checkError(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?", dev_a, dev_c);

	cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_c);

	cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_c);

	cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_c);

	cudaEvent_t start, stop; //описываем переменные типа  cudaEvent_t 
	float gpuTime = 0.0f;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	// вызов основной функции вычисления префиксных сумм
	prefixSumKernel(dev_a, dev_c, size, threadsCount);

	cudaStatus = cudaGetLastError();
	checkError(cudaStatus, "prefixSum2Kernel launch failed: %s\n", dev_a, dev_c);

	cudaStatus = cudaDeviceSynchronize();
	checkError(cudaStatus, "cudaDeviceSynchronize returned error code %d after launching prefixSum2Kernel!\n", dev_a, dev_c);

	cudaEventRecord(stop, 0);

	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&gpuTime, start, stop);
	printf("time spent executing by the GPU: %.5f ms\n", gpuTime);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
	checkError(cudaStatus, "cudaMemcpy failed!", dev_a, dev_c);

	return cudaStatus;
}

void prefixSumKernel(int* inData, int* outData, int& arraySize, int& blockSize, int sharedSize, void(*prefixSum) (int* inData, int* outData, int* sums, int arraySize))
{
	int numBlocks = ceil((double)arraySize / (2 * blockSize));
	int* sums; // суммы элементов для каждого блока, посчитанные для массива inData
	int* resultSums; // суммы элементов для каждого блока, посчитанные для массива sums (рекурсия)

	if (numBlocks < 1) {
		numBlocks = 1;
	}

	cudaMalloc((void**)&sums, numBlocks * sizeof(int));
	cudaMalloc((void**)&resultSums, numBlocks * sizeof(int));

	// вычисляем суммы для inData
	dim3 threads(blockSize, 1, 1), blocks(numBlocks, 1, 1);
	prefixSum<< <blocks, threads, sharedSize * sizeof(int) >> > (inData, outData, sums, 2 * blockSize);

	int* testRes = (int*)malloc(numBlocks * sizeof(int));
	cudaMemcpy(testRes, sums, numBlocks * sizeof(int), cudaMemcpyDeviceToHost);

	// вычисляем суммы для sums
	// тут рекурсия
	if (arraySize >= 2 * blockSize)
		prefixSumKernel(sums, resultSums, numBlocks, blockSize, sharedSize, prefixSum);
	else
		cudaMemcpy(resultSums, sums, numBlocks * sizeof(int), cudaMemcpyDeviceToDevice);

	cudaError_t cudaStatus = cudaGetLastError();
	// корректируем результат 
	threads = dim3(2 * blockSize, 1, 1);
	if (numBlocks <= 1) {
		blocks = dim3(1, 1, 1);
	}
	else {
		blocks = dim3(numBlocks - 1, 1, 1);
	}

	// передаем в функцию адреса со смещением
	// пропускаем первый блок
	finalPrefixSum << <blocks, threads >> > (outData + 2 * blockSize, resultSums + 1, arraySize, blockSize);
	cudaStatus = cudaGetLastError();
	cudaFree(resultSums);
	cudaStatus = cudaGetLastError();
	cudaFree(sums);
	cudaStatus = cudaGetLastError();
}

void prefixSumKernel1(int* inData, int* outData, int& arraySize, int& blockSize) {
	int sharedSize = 2 * blockSize;
	prefixSumKernel(inData, outData, arraySize, blockSize, sharedSize, prefixSum1);
}

void prefixSumKernel2(int* inData, int* outData, int& arraySize, int& blockSize) {
	int sharedSize = 2 * blockSize + ((2 * blockSize) >> 4);
	prefixSumKernel(inData, outData, arraySize, blockSize, sharedSize, prefixSum2);

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

void validate(int* result, int* array, int arraySize) {
	int v = 0;
	for (size_t i = 0; i < arraySize - 1; i++)
	{
		v += array[i];
		if (result[i+1] != v) {
			printf("\nWrong answer on step %d (%d != %d).", i+1, v, result[i+1]);
			//return;
			v = result[i + 1];
		}
	}
	printf("Answer success\n");
}