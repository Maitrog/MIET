
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void cuda_hello() {
	printf("Hello World from GPU!\n");
}

int main() {
	int		deviceCount;
	cudaDeviceProp	devProp;

	cudaGetDeviceCount(&deviceCount);
	printf("Found %d devices\n", deviceCount);

	for (int device = 0; device < deviceCount; device++)
	{
		cudaGetDeviceProperties(&devProp, device);
		printf("Device %d\n", device);
		printf("Compute capability     : %d.%d\n", devProp.major, devProp.minor);
		printf("Name                   : %s\n", devProp.name);
		printf("Total Global Memory    : %u\n", devProp.totalGlobalMem);
		printf("Shared memory per block: %d\n", devProp.sharedMemPerBlock);
		printf("Registers per block    : %d\n", devProp.regsPerBlock);
		printf("Warp size              : %d\n", devProp.warpSize);
		printf("Max threads per block  : %d\n", devProp.maxThreadsPerBlock);
		printf("Total constant memory  : %d\n", devProp.totalConstMem);
		printf("maxBlocksPerMultiProcessor  : %d\n", devProp.maxBlocksPerMultiProcessor);
		printf("maxThreadsPerMultiProcessor  : %d\n", devProp.maxThreadsPerMultiProcessor);
		printf("Multiprocessor count  : %d\n", devProp.multiProcessorCount);

	}

	cudaEvent_t start, stop;		//описываем переменные типа  cudaEvent_t 
	float       gpuTime = 0.0f;
	// создаем события начала и окончания выполнения ядра 
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	//привязываем событие start  к данному месту 
	cudaEventRecord(start, 0);

	// вызвать ядро 
	cuda_hello << <1, 1 >> > ();

	//привязываем событие stop  к данному месту 
	cudaEventRecord(stop, 0);

	cudaEventSynchronize(stop);
	// запрашиваем время между событиями 
	cudaEventElapsedTime(&gpuTime, start, stop);
	printf("time spent executing by the GPU: %.5f ms\n", gpuTime);
	// уничтожаем созданные события 
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	return 0;
}
