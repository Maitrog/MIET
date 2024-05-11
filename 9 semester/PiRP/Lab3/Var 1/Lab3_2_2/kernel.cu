/*
 * Parallel bitonic sort using CUDA.
 * Compile with
 * nvcc -arch=sm_11 bitonic_sort.cu
 * Based on http://www.tools-of-computing.com/tc/CS/Sorts/bitonic_sort.htm
 * License: BSD 3
 */

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

 /* Every thread gets exactly one value in the unsorted array. */
#define THREADS 256 // 2^9

void validate(float* result, int arraySize) {
    int v = 0;
    for (size_t i = 0; i < arraySize - 1; i++)
    {
        if (result[i] > result[i + 1]) {
            printf("Wrong answer\n");
            return;
        }
    }
    printf("\nAnswer success");
}

float random_float()
{
    return (float)rand() / (float)RAND_MAX;
}

void array_print(float* arr, int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%1.3f ", arr[i]);
    }
    printf("\n");
}

void array_fill(float* arr, int length)
{
    //srand(time(NULL));
    int i;
    for (i = 0; i < length; ++i) {
        arr[i] = random_float();
    }
}

float* resizeArray(float* values, int arraySize, int newArraySize)
{
    float* newValues = (float*)malloc(newArraySize * sizeof(float));
    int d = newArraySize - arraySize;
    for (size_t i = 0; i < newArraySize; i++)
    {
        if (i < arraySize)
        {
            newValues[i] = values[i];
        }
        else
        {
            newValues[i] = INT_MAX;
        }
    }

    return newValues;
}

__global__ void bitonic_sort_step(float* dev_values, int j, int k)
{
    unsigned int i, ixj; /* Sorting partners: i and ixj */
    i = threadIdx.x + blockDim.x * blockIdx.x;
    ixj = i ^ j;

    /* The threads with the lowest ids sort the array. */
    if ((ixj) > i) {
        if ((i & k) == 0) {
            /* Sort ascending */
            if (dev_values[i] > dev_values[ixj]) {
                /* exchange(i,ixj); */
                float temp = dev_values[i];
                dev_values[i] = dev_values[ixj];
                dev_values[ixj] = temp;
            }
        }
        if ((i & k) != 0) {
            /* Sort descending */
            if (dev_values[i] < dev_values[ixj]) {
                /* exchange(i,ixj); */
                float temp = dev_values[i];
                dev_values[i] = dev_values[ixj];
                dev_values[ixj] = temp;
            }
        }
    }
}

/**
 * Inplace bitonic sort using CUDA.
 */
float* bitonic_sort(float* values, int arraySize)
{
    int stepsCount = ceil(log2(arraySize));
    int newArraySize = pow(2, stepsCount);
    values = resizeArray(values, arraySize, newArraySize);

    float* dev_values;
    size_t size = newArraySize * sizeof(float);

    cudaMalloc((void**)&dev_values, size);
    cudaMemcpy(dev_values, values, size, cudaMemcpyHostToDevice);

    int blocksCount = ceil(newArraySize / THREADS);
    dim3 blocks(blocksCount, 1);    /* Number of blocks   */
    dim3 threads(THREADS, 1);  /* Number of threads  */
    
    int j, k;
    /* Major step */
    for (k = 2; k <= newArraySize; k <<= 1) {
        /* Minor step */
        for (j = k >> 1; j > 0; j = j >> 1) {
            bitonic_sort_step << <blocks, threads >> > (dev_values, j, k);
        }
    }
    cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
    cudaFree(dev_values);

    return values;
}

int main(void)
{
    printf("Enter array size: ");
    int arraySize;
    scanf("%d", &arraySize);

    float* values = (float*)malloc(arraySize * sizeof(float));
    array_fill(values, arraySize);
    //array_print(values, arraySize);

    values = bitonic_sort(values, arraySize);

    printf("\n");
    //array_print(values, arraySize);
    validate(values, arraySize);
}
