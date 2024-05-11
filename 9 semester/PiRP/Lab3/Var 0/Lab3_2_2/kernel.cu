
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void printArray(int* a, int size);

void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_c);

void validate(int* result, int* array, int arraySize);

cudaError_t histogramWithCuda(int *c, const int *a, unsigned int size, int threadSize);

__global__ void histogramSmemAtomics(const int* in, int size, int NUM_BINS, int* out)
{
    // pixel coordinates
    int x = blockIdx.x * blockDim.x + threadIdx.x;

    // step in block
    int nx = blockDim.x * gridDim.x;

    // linear thread index within block
    int t = threadIdx.x;

    // total threads in block
    int nt = blockDim.x;

    // block index
    int bx = blockIdx.x;

    // initialize temporary accumulation array in shared memory
    extern __shared__ unsigned int smem[];
    for (int i = t; i < NUM_BINS; i += nt) {
        smem[i] = 0;
    }

    __syncthreads();
    // updates our block's partial histogram in shared memory
    for (int col = x; col < size; col += nx)
    {
        unsigned int r = (unsigned int)(in[col]);
        //printf("%d: %d\n", col, in[col]);
        atomicAdd(&smem[r], 1);
    }
    __syncthreads();

    // write partial histogram into the global memory
    out += bx * NUM_BINS;
    for (int i = t; i < NUM_BINS; i += nt) {
        out[i] = smem[i];
    }
}

__global__ void histogramFinalAccum(const int* in, int NUM_BINS, int NUM_PARTS, int* out)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < NUM_BINS) {
        unsigned int total = 0;
        for (int j = 0; j < NUM_PARTS; j++) {
            total += in[i + NUM_BINS * j];
        }
        out[i] = total;
    }
}

int main()
{
    printf("Enter array size: ");
    int arraySize;
    scanf("%d", &arraySize);
    int threadSize = 256;
    int* a = (int*)malloc(arraySize * sizeof(int));
    int* c = (int*)malloc(256 * sizeof(int));
    for (size_t i = 0; i < arraySize; i++)
    {
        a[i] = rand() % 256;
    }

    // Add vectors in parallel.
    cudaError_t cudaStatus = histogramWithCuda(c, a, arraySize, threadSize);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "histogramWithCuda failed!");
        return 1;
    }

    /*for (size_t i = 0; i < 256; i++)
    {
        printf("%d: %d\n", i, c[i]);
    }*/
    validate(c, a, arraySize);

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
cudaError_t histogramWithCuda(int* c, const int* a, unsigned int size, int threadSize)
{
    int NUM_BINS = 256;
    int PART_SIZE = size < 300000 ? 3000 : 10000;
    int NUM_PARTS = ceil(double(size) / PART_SIZE);
    int *input = 0;
    int *dev_c = 0;
    int* result = 0;
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    checkError(cudaStatus, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?", input, dev_c);

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_c, 256 * NUM_PARTS * sizeof(int));
    checkError(cudaStatus, "cudaMalloc failed!", input, dev_c);

    cudaStatus = cudaMalloc((void**)&result, 256 * sizeof(int));
    checkError(cudaStatus, "cudaMalloc failed!", input, dev_c);

    cudaStatus = cudaMalloc((void**)&input, size * sizeof(int));
    checkError(cudaStatus, "cudaMalloc failed!", input, dev_c);

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(input, a, size * sizeof(int), cudaMemcpyHostToDevice);
    checkError(cudaStatus, "cudaMemcpy failed!", input, dev_c);
    
    cudaEvent_t start, stop;
    float       gpuTime = 0.0f;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    histogramSmemAtomics <<<NUM_PARTS, threadSize, NUM_BINS * sizeof(int) >> >(input, size, NUM_BINS, dev_c);
    cudaStatus = cudaGetLastError();
    checkError(cudaStatus, "histogramSmemAtomics launch failed: %s\n", input, dev_c);

    histogramFinalAccum << <2, NUM_BINS >> > (dev_c, NUM_BINS, NUM_PARTS, result);
    cudaStatus = cudaGetLastError();
    checkError(cudaStatus, "histogramFinalAccum launch failed: %s\n", input, dev_c);

    cudaStatus = cudaDeviceSynchronize();
    checkError(cudaStatus, "cudaDeviceSynchronize returned error code %d after launching multiplyKernel!\n", input, dev_c);
    cudaEventRecord(stop, 0);

    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpuTime, start, stop);
    printf("time spent executing by the GPU: %.5f ms\n", gpuTime);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(c, result, 256 * sizeof(int), cudaMemcpyDeviceToHost);
    checkError(cudaStatus, "cudaMemcpy failed!", input, dev_c);

    
    return cudaStatus;
}


void checkError(cudaError_t cudaStatus, char* msg, int* dev_a, int* dev_c)
{
    if (cudaStatus == cudaSuccess)
        return;

    printf("cudaStatus: %d\n", cudaStatus);
    printf(msg);
    cudaFree(dev_a);
    cudaFree(dev_c);
}

void printArray(int* a, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
}

void validate(int* result, int* array, int arraySize) {
    int* test = new int[256];
    for (int i = 0; i < 256; i++)
        test[i] = 0;
    for (int i = 0; i < arraySize; i++)
        test[array[i]]++;

    for (int i = 0; i < 256; i++)
    {
        if (result[i] != test[i]) {
            printf("\nWrong answer (%d: %d != %d)", i, test[i], result[i]);
        }
    }

    printf("\nAnswer success");
}