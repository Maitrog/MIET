#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define CL_USE_DEPRECATED_OPENCL_2_2_APIS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/opencl.h>
#include <algorithm>
#include <CL/cl_ext_intel.h>

#include <CL/cl.h>
#include "CL/cl2.hpp"
#include "CL/opencl.h"
#include "CL/opencl.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

constexpr short EXIT_STATUS_ERROR = -1;

// OpenCL kernel. Each work item takes care of one element of c
const char* kernelSource = "\n" \
"#pragma OPENCL EXTENSION cl_khr_fp64 : enable                   \n" \
"__kernel void task2(   __global double *x,                      \n" \
"                       __global double *Y,                      \n" \
"                       __global double *res,                    \n" \
"                       const int a,                             \n" \
"                       const unsigned int n)                    \n" \
"{                                                               \n" \
"    //Get our position                                          \n" \
"    int row = get_global_id(0);                                 \n" \
"    //int index = (row * N) + col;                              \n" \
"    if (row < 0 || row > n) return;                             \n" \
"                                                                \n" \
"    int sum = 0;                                                \n" \
"    for (int col = 0; col < n; col++) {                         \n" \
"        sum += Y[row * n + col] * x[row];                       \n" \
"    }                                                           \n" \
"    res[row] = sum;                                             \n" \
"}                                                               \n" \
"__kernel void task1(   __global double *a,                      \n" \
"                       __global double *b,                      \n" \
"                       __global double *c,                      \n" \
"                       __global double *res,                    \n" \
"                       const int x,                             \n" \
"                       const int y,                             \n" \
"                       const unsigned int n)                    \n" \
"{                                                               \n" \
"    //Get our global thread ID                                  \n" \
"    int id = get_global_id(0);                                  \n" \
"                                                                \n" \
"    //Make sure we do not go out of bounds                      \n" \
"    if (id < n && id >= 0)                                      \n" \
"        res[id] = x * a[id] + y * b[id] * c[id];                \n" \
"}                                                               \n" \
"\n";

// ”становка требуемой платформы и девайса по типу девайса
// @param cpPlatform - платформа
// @param device_ide - девайс
// @param type - типа девайса
void set_platform_and_device(cl_platform_id& cpPlatform, cl_device_id& device_id, cl_device_type type)
{
    cl_uint num_platforms;
    clGetPlatformIDs(0, NULL, &num_platforms);

    cl_platform_id* platforms = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id));
    clGetPlatformIDs(num_platforms, platforms, NULL);

    for (int i = 0; i < num_platforms; i++) {
        cl_uint num_devices;
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);

        if (num_devices > 0) {
            cl_device_id* devices = (cl_device_id*)malloc(num_devices * sizeof(cl_device_id));
            clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

            for (int j = 0; j < num_devices; j++) {
                // Get device name
                char device_name[128];
                clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(device_name), &device_name, NULL);

                // Get device type
                cl_device_type device_type;
                clGetDeviceInfo(devices[j], CL_DEVICE_TYPE, sizeof(device_type), &device_type, NULL);

                if (device_type & type)
                {
                    cpPlatform = platforms[i];
                    device_id = devices[j];

                    free(devices);
                    free(platforms);
                    return;
                }
            }

            free(devices);
        }
    }

    free(platforms);
}

// ѕроверка статуса кода. ¬ случае ошибочного кода программа завершаетс€
// @param error_code - статус open cl
void check_error_code(cl_int error_code)
{
    switch (error_code)
	{
	case CL_INVALID_CONTEXT:  printf("if context is not a valid context.\n");
		break;
	case CL_INVALID_DEVICE: printf("if device is not a valid device or is not associated with context.\n");
		break;
	case CL_INVALID_VALUE: printf("if values specified in properties are not valid.\n");
		break;
	case CL_INVALID_QUEUE_PROPERTIES: printf("if values specified in properties are valid but are not supported by the device.\n");
		break;
	case CL_OUT_OF_RESOURCES: printf("if there is a failure to allocate resources required by the OpenCL implementation on the device.\n");
		break;
	case CL_OUT_OF_HOST_MEMORY: printf("if there is a failure to allocate resources required by the OpenCL implementation on the host.\n");
		break;
    case CL_INVALID_PROGRAM:  printf(" if program is not a valid program object.\n");
        break;
    case CL_INVALID_BINARY:  printf(" if program is created with clCreateWithProgramWithBinary and devices listed in device_list do not have a valid program binary loaded.\n");
        break;
    case CL_INVALID_BUILD_OPTIONS:  printf(" if the build options specified by options are invalid.\n");
        break;
    case CL_INVALID_OPERATION:  printf(" if the build of a program executable for any of the devices listed in device_list by a previous call to clBuildProgram for program has not completed.\n");
        break;
    case CL_COMPILER_NOT_AVAILABLE:  printf(" if program is created with clCreateProgramWithSource and a compiler is not available i.e.CL_DEVICE_COMPILER_AVAILABLE specified in the table of OpenCL Device Queries for clGetDeviceInfo is set to CL_FALSE.\n");
        break;
    case CL_BUILD_PROGRAM_FAILURE:  printf(" if there is a failure to build the program executable.This error will be returned if clBuildProgram does not return until the build has completed.\n");
        break;
    case CL_INVALID_PROGRAM_EXECUTABLE:  printf("  if there is no successfully built program executable available for device associated with command_queue..\n");
        break;
    case CL_INVALID_COMMAND_QUEUE:  printf("  if command_queue is not a valid command - queue..\n");
        break;
    case CL_INVALID_KERNEL:  printf("  if kernel is not a valid kernel object..\n");
        break;
    case CL_INVALID_KERNEL_ARGS:  printf("  if the kernel argument values have not been specified..\n");
        break;
    case CL_INVALID_WORK_DIMENSION:  printf(" if work_dim is not a valid value(i.e.a value between 1 and 3)..\n");
        break;
    case CL_INVALID_WORK_GROUP_SIZE:  printf(" if local_work_size is specified and number of work - items specified by global_work_size is not evenly divisable by size of work - group given by local_work_size or does not match the work - group size specified for kernel using the __attribute__((reqd_work_group_size(X, Y, Z))) qualifier in program source..\n");
        break;
    case CL_INVALID_WORK_ITEM_SIZE:  printf(" if the number of work - items specified in any of local_work_size[0], ... local_work_size[work_dim - 1] is greater than the corresponding values specified by CL_DEVICE_MAX_WORK_ITEM_SIZES[0], ....CL_DEVICE_MAX_WORK_ITEM_SIZES[work_dim - 1]..\n");
        break;
    case CL_INVALID_GLOBAL_OFFSET:  printf(" if global_work_offset is not NULL..\n");
        break;
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:  printf(" if there is a failure to allocate memory for data store associated with image or buffer objects specified as arguments to kernel..\n");
        break;
    case CL_INVALID_EVENT_WAIT_LIST:  printf(" if event_wait_list is NULL and num_events_in_wait_list > 0, or event_wait_list is not NULL and num_events_in_wait_list is 0, or if event objects in event_wait_list are not valid events..\n");
        break;
	default:
        return;
	}

    printf(" bye bye \n");
    exit(EXIT_STATUS_ERROR);
}

// ‘ункци€ вычислени€ w = a * Y * x
// @param n - размерность матрицы (Y) и вектора (x)
// @param a - параметр a
// @param device_type - типа девайса из набора CL_DEVICE_TYPE_*
// @return - врем€, затраченное на операцию
double task2(const unsigned int n, const int a, cl_int device_type)
{
    // Host input vectors
    double* x;
    double* Y;
    // Host output vector
    double* res;

    // Device input buffers
    cl_mem d_x;
    cl_mem d_Y;
    // Device output buffer
    cl_mem d_res;

    cl_platform_id cpPlatform;        // OpenCL platform
    cl_device_id device_id;           // device ID
    cl_context context;               // context
    cl_command_queue queue;           // command queue
    cl_program program;               // program
    cl_kernel kernel;                 // kernel

    // Size, in bytes, of each vector
    size_t bytes = n * sizeof(double);

    // Allocate memory for each vector on host
    x = (double*)malloc(bytes);
    Y = (double*)malloc(n * n * sizeof(double)); // Square matrix
    res = (double*)malloc(bytes);

    // Initialize vectors on host
    for (int i = 0; i < n; i++)
    {
        x[i] = 1;
        res[i] = 0;
    }

    // Initialize square matrix
    for (int i = 0; i < n * n; i++)
    {
        Y[i] = 1;
    }

    size_t globalSize, localSize;
    cl_int err;

    // Number of work items in each local work group
    //localSize = 64;
    localSize = 1;

    // Number of total work items - localSize must be devisor
    //globalSize = ceil(n / (float)localSize) * localSize;
    //globalSize = std::min((unsigned int)256, n);
    globalSize = n;
    printf("Thread count: %d \n", globalSize);

    // Bind to platform and device
    set_platform_and_device(cpPlatform, device_id, device_type);

    // Bind to platform
    //err = clGetPlatformIDs(2, &cpPlatform, NULL);
    //check_error_code(err);

    //// Get ID for the device
    //err = clGetDeviceIDs(cpPlatform, device_type, 2, &device_id, NULL);
    //check_error_code(err);

    // Create a context 
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);

    // Create a command queue
    queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &err);

    // Create the compute program from the source buffer
    program = clCreateProgramWithSource(context, 1,
        (const char**)&kernelSource, NULL, &err);

    // Build the program executable
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    // Create the compute kernel in the program we wish to run
    kernel = clCreateKernel(program, "task2", &err);

    // Create the input and output arrays in device memory for our calculation
    d_x = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    d_Y = clCreateBuffer(context, CL_MEM_READ_ONLY, n * n * sizeof(double), NULL, NULL);
    d_res = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);

    // Write our data set into the input array in device memory
    err = clEnqueueWriteBuffer(queue, d_x, CL_TRUE, 0,
        bytes, x, 0, NULL, NULL);
    check_error_code(err);
    err |= clEnqueueWriteBuffer(queue, d_Y, CL_TRUE, 0,
        n * n * sizeof(double), Y, 0, NULL, NULL);
    check_error_code(err);

    // Set the arguments to our compute kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_x);
    check_error_code(err);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_Y);
    check_error_code(err);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_res);
    check_error_code(err);
    err |= clSetKernelArg(kernel, 3, sizeof(int), &a);
    check_error_code(err);
    err |= clSetKernelArg(kernel, 4, sizeof(unsigned int), &n);
    check_error_code(err);

    // Execute the kernel over the entire range of the data set 
    cl_event event;

    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize,
        0, NULL, &event);
    clWaitForEvents(1, &event);

    // Wait for the command queue to get serviced before reading back results
    clFinish(queue);

    check_error_code(err);

    cl_ulong time_start;
    cl_ulong time_end;

    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

    double nanoSeconds = time_end - time_start;
    
    // Read the results from the device
    clEnqueueReadBuffer(queue, d_res, CL_TRUE, 0,
        bytes, res, 0, NULL, NULL);

    //Sum up vector c and print result divided by n, this should equal 1 within error
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += res[i];
    printf("final result: %f\n", sum);

    // release OpenCL resources
    clReleaseMemObject(d_x);
    clReleaseMemObject(d_Y);
    clReleaseMemObject(d_res);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    //release host memory
    free(x);
    free(Y);
    free(res);

    return nanoSeconds / 1000000.0;
}

// ‘ункци€ вычислени€ w = x * a + y * b * c
// @param n - размерность матрицы (Y) и вектора (x)
// @param x - параметр x
// @param y - параметр Y
// @param device_type - типа девайса из набора CL_DEVICE_TYPE_*
// @return - врем€, затраченное на операцию
double task1(const unsigned int n, const int x, const int y, cl_int device_type)
{
    // Host input vectors
    double* h_a;
    double* h_b;
    double* h_c;
    // Host output vector
    double* h_res;

    // Device input buffers
    cl_mem d_a;
    cl_mem d_b;
    cl_mem d_c;
    // Device output buffer
    cl_mem d_res;

    cl_platform_id cpPlatform;        // OpenCL platform
    cl_device_id device_id;           // device ID
    cl_context context;               // context
    cl_command_queue queue;           // command queue
    cl_program program;               // program
    cl_kernel kernel;                 // kernel

    // Size, in bytes, of each vector
    size_t bytes = n * sizeof(double);

    // Allocate memory for each vector on host
    h_a = (double*)malloc(bytes);
    h_b = (double*)malloc(bytes);
    h_c = (double*)malloc(bytes);
    h_res = (double*)malloc(bytes);

    // Initialize vectors on host
    int i;
    for (i = 0; i < n; i++)
    {
        //h_a[i] = sinf(i) * sinf(i);
        //h_b[i] = cosf(i) * cosf(i);
        h_a[i] = 1;
        h_b[i] = 1;
        h_c[i] = 1;
    }

    size_t globalSize, localSize;
    cl_int err;

    // Number of work items in each local work group
    localSize = 64;

    // Number of total work items - localSize must be devisor
    globalSize = ceil(n / (float)localSize) * localSize;

    // Bind to platform and device
    set_platform_and_device(cpPlatform, device_id, device_type);

    // Bind to platform
    //err = clGetPlatformIDs(1, &cpPlatform, NULL);

    // Get ID for the device
    //err = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

    // Create a context 
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);

    // Create a command queue
    queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &err);

    // Create the compute program from the source buffer
    program = clCreateProgramWithSource(context, 1,
        (const char**)&kernelSource, NULL, &err);

    // Build the program executable
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    // Create the compute kernel in the program we wish to run
    kernel = clCreateKernel(program, "task1", &err);

    // Create the input and output arrays in device memory for our calculation
    d_a = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    d_b = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    d_c = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    d_res = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);

    // Write our data set into the input array in device memory
    err = clEnqueueWriteBuffer(queue, d_a, CL_TRUE, 0,
        bytes, h_a, 0, NULL, NULL);
    check_error_code(err);
    err |= clEnqueueWriteBuffer(queue, d_b, CL_TRUE, 0,
        bytes, h_b, 0, NULL, NULL);
    check_error_code(err);
    err |= clEnqueueWriteBuffer(queue, d_c, CL_TRUE, 0,
        bytes, h_c, 0, NULL, NULL);
    check_error_code(err);

    // Set the arguments to our compute kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
    err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &d_res);
    err |= clSetKernelArg(kernel, 4, sizeof(int), &x);
    err |= clSetKernelArg(kernel, 5, sizeof(int), &y);
    err |= clSetKernelArg(kernel, 6, sizeof(unsigned int), &n);
    check_error_code(err);

    // Execute the kernel over the entire range of the data set 
    cl_event event;

    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize,
        0, NULL, &event);

    clWaitForEvents(1, &event);

    // Wait for the command queue to get serviced before reading back results
    clFinish(queue);

    check_error_code(err);

    cl_ulong time_start;
    cl_ulong time_end;

    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

    double nanoSeconds = time_end - time_start;

    // Read the results from the device
    clEnqueueReadBuffer(queue, d_res, CL_TRUE, 0,
        bytes, h_res, 0, NULL, NULL);

    //Sum up vector c and print result divided by n, this should equal 1 within error
    double sum = 0;
    for (i = 0; i < n; i++)
        sum += h_res[i];
    printf("final result: %f\n", sum);

    // release OpenCL resources
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseMemObject(d_res);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    //release host memory
    free(h_a);
    free(h_b);
    free(h_c);
    free(h_res);

    return nanoSeconds / 1000000.0;
}

int main(int argc, char* argv[])
{
    for (int i = 12; i < 13; i++)
    {
        auto time = task2(pow(2, i), 1, CL_DEVICE_TYPE_CPU);
        printf("Execution number %d \n", i - 1);
        printf("Execution time: %f ms\n", time);
    }

    //for (int i = 10; i < 11; i++)
    //{
    //    auto time = task1(pow(2, i), 1, 1, CL_DEVICE_TYPE_GPU);
    //    printf("Execution number %d \n", i - 1);
    //    printf("Execution time: %f ms\n", time);
    //}
}
