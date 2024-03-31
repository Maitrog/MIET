
#include <CL/opencl.hpp>
#include <CL/cl_platform.h>

#include <iostream>

double task1(const int n, cl::Platform platform);

double task2(const int n, cl::Platform platform);


int main()
{
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);

    if (all_platforms.size() == 0) {
        std::cout << " No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    // use all_platforms[0] because that's a GPU; all_platforms[1] is the CPU
    cl::Platform platform_gpu = all_platforms[0];
    cl::Platform platform_cpu = all_platforms[1];

    for (int i = 1; i < 29; i++) {
        int dim = pow(2, i);
        double time = task1(dim, platform_gpu);
        std::cout << "Dim: " << dim << " GPU Time: " << time << "\n";

        double time = task1(dim, platform_cpu);
        std::cout << "Dim: " << dim << " CPU Time: " << time << "\n";
    }

    return 0;
}

double task1(const int n, cl::Platform platform) {
    cl_int errcode_ret;
    std::vector<cl::Device> all_devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0) {
        std::cout << " No devices found. Check OpenCL installation!\n";
        exit(1);
    }

    cl::Device default_device = all_devices[0];
    std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";

    // a context is like a "runtime link" to the device and platform;
    // i.e. communication is possible
    cl::Context context({ default_device });

    // create the program that we want to execute on the device
    cl::Program::Sources sources;

    // calculates for each element; w = a * x + b * y * z
    std::string kernel_code_task1 =
        "   void kernel task1(__global int* X, __global int* Y, __global int* Z, __global int* W, "
        "                          __global int* N, __global int* params) {"
        "       int ID, Nthreads, n, ratio, start, stop;"
        ""
        "       ID = get_global_id(0);"
        "       Nthreads = get_global_size(0);"
        "       n = N[0];"
        "       int a = params[0];"
        "       int b = params[1];"
        ""
        "       ratio = (n / Nthreads);"  // number of elements for each thread
        "       start = ratio * ID;"
        "       stop  = ratio * (ID + 1);"
        ""
        "       for (int i=start; i<stop && i < n; i++)"
        "       {"
        "           W[i] = a * X[i] + b * Y[i] * Z[i];"
        "       }"
        "   }";
    kernel_code_task1 = 
        "   void kernel task1(__global int* X, __global int* Y, __global int* Z, __global int* W, "
        "                          __global int* N, __global int* params) {"
        "       int ID, Nthreads, n, ratio, start, stop;"
        ""
        "       ID = get_global_id(0);"
        "       n = N[0];"
        "       int a = params[0];"
        "       int b = params[1];"
        ""
        "       W[ID] = a * X[ID] + b * Y[ID] * Z[ID];"
        "   }";
    sources.push_back({ kernel_code_task1.c_str(), kernel_code_task1.length() });

    cl::Program program(context, sources);
    if (program.build({ default_device }) != CL_SUCCESS) {
        std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
        exit(1);
    }

    // apparently OpenCL only likes arrays ...
    // N holds the number of elements in the vectors we want to add
    int N[1] = { n };

    // create things on here (CPU)
    int params[2];
    int* X, * Y, * Z, * W;
    X = (int*)malloc(n * sizeof(int));
    Y = (int*)malloc(n * sizeof(int));
    Z = (int*)malloc(n * sizeof(int));
    W = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        X[i] = 1;
        Y[i] = 2;
        Z[i] = 3;
    }
    params[0] = 2;
    params[1] = 3;

    cl::Event event;
    std::clock_t start_time = std::clock();
    // create buffers on device (allocate space on GPU)
    cl::Buffer buffer_X(context, CL_MEM_READ_ONLY, sizeof(int) * n, NULL, &errcode_ret);
    cl::Buffer buffer_Y(context, CL_MEM_READ_ONLY, sizeof(int) * n, NULL, &errcode_ret);
    cl::Buffer buffer_Z(context, CL_MEM_READ_ONLY, sizeof(int) * n, NULL, &errcode_ret);
    cl::Buffer buffer_W(context, CL_MEM_READ_WRITE, sizeof(int) * n, NULL, &errcode_ret);
    cl::Buffer buffer_Params(context, CL_MEM_READ_ONLY, sizeof(int) * 2, NULL, &errcode_ret);
    cl::Buffer buffer_N(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &errcode_ret);
    if (errcode_ret != CL_SUCCESS)
    {
        printf("Error to create buffer");
        return 0;
    }

    // create a queue (a queue of commands that the GPU will execute)
    cl::CommandQueue queue(context, default_device, CL_QUEUE_PROFILING_ENABLE, &errcode_ret);
    if (errcode_ret != CL_SUCCESS)
    {
        printf("Error to create queue");
        return 0;
    }

    // push write commands to queue
    queue.enqueueWriteBuffer(buffer_X, CL_TRUE, 0, sizeof(int) * n, X);
    queue.enqueueWriteBuffer(buffer_Y, CL_TRUE, 0, sizeof(int) * n, Y);
    queue.enqueueWriteBuffer(buffer_Z, CL_TRUE, 0, sizeof(int) * n, Z);
    queue.enqueueWriteBuffer(buffer_Params, CL_TRUE, 0, sizeof(int) * 2, params);
    queue.enqueueWriteBuffer(buffer_N, CL_TRUE, 0, sizeof(int), N);

    // RUN ZE KERNEL
    cl::Kernel kernel(program, "task1");
    kernel.setArg(0, buffer_X);
    kernel.setArg(1, buffer_Y);
    kernel.setArg(2, buffer_Z);
    kernel.setArg(3, buffer_W);
    kernel.setArg(4, buffer_N);
    kernel.setArg(5, buffer_Params);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(n), cl::NullRange, NULL, &event);

    // read result from GPU to here
    queue.enqueueReadBuffer(buffer_W, CL_TRUE, 0, sizeof(int) * n, W);
    event.wait();
    queue.finish();

    cl_ulong time_start;
    cl_ulong time_end;
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &time_end);
    cl_int tt2 = event.getProfilingInfo(CL_PROFILING_COMMAND_START, &time_start);
    double time = time_end - time_start;

    return time;
}

double task2(const int n, cl::Platform platform) {
    cl_int errcode_ret;
    std::vector<cl::Device> all_devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0) {
        std::cout << " No devices found. Check OpenCL installation!\n";
        exit(1);
    }

    cl::Device default_device = all_devices[0];
    std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";

    // a context is like a "runtime link" to the device and platform;
    // i.e. communication is possible
    cl::Context context({ default_device });

    // create the program that we want to execute on the device
    cl::Program::Sources sources;

    // calculates for each element; w = a * x + b * y * z
    std::string kernel_code_task1 =
        "   void kernel task1(__global int* x, __global int* Y, __global int* W, "
        "                          __global int* N, __global int* params) {"
        "       int row = get_global_id(0);          " 
        "       int n = N[0];"
        "       int a = params[0];"
        "       if (row < 0 || row > n) return;      " 
        "                                            " 
        "       int sum = 0;                         " 
        "       for (int col = 0; col < n; col++) {  " 
        "           sum += Y[row * n + col] * x[row];" 
        "       }                                    " 
        "       W[row] = sum;                      " 
        "   }";
    sources.push_back({ kernel_code_task1.c_str(), kernel_code_task1.length() });

    cl::Program program(context, sources);
    if (program.build({ default_device }) != CL_SUCCESS) {
        std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
        exit(1);
    }

    // apparently OpenCL only likes arrays ...
    // N holds the number of elements in the vectors we want to add
    int N[1] = { n };

    // create things on here (CPU)
    int params[1];
    int* X, * Y, * W;
    X = (int*)malloc(n * sizeof(int));
    Y = (int*)malloc(n * n * sizeof(int));
    W = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        X[i] = rand() % 10;
        for (int j = 0; j < n; j++) {
            Y[i * n + j] = rand() % 10;
        }
    }
    params[0] = 2;

    cl::Event event;
    // create buffers on device (allocate space on GPU)
    cl::Buffer buffer_X(context, CL_MEM_READ_ONLY, sizeof(int) * n, NULL, &errcode_ret);
    cl::Buffer buffer_Y(context, CL_MEM_READ_ONLY, sizeof(int) * n * n, NULL, &errcode_ret);
    cl::Buffer buffer_W(context, CL_MEM_READ_WRITE, sizeof(int) * n, NULL, &errcode_ret);
    cl::Buffer buffer_Params(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &errcode_ret);
    cl::Buffer buffer_N(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &errcode_ret);
    if (errcode_ret != CL_SUCCESS)
    {
        printf("Error to create buffer");
        return 0;
    }

    // create a queue (a queue of commands that the GPU will execute)
    cl::CommandQueue queue(context, default_device, CL_QUEUE_PROFILING_ENABLE, &errcode_ret);
    if (errcode_ret != CL_SUCCESS)
    {
        printf("Error to create queue");
        return 0;
    }

    // push write commands to queue
    queue.enqueueWriteBuffer(buffer_X, CL_TRUE, 0, sizeof(int) * n, X, NULL, &event);
    queue.enqueueWriteBuffer(buffer_Y, CL_TRUE, 0, sizeof(int) * n * n, Y, NULL, &event);
    queue.enqueueWriteBuffer(buffer_Params, CL_TRUE, 0, sizeof(int), params, NULL, &event);
    queue.enqueueWriteBuffer(buffer_N, CL_TRUE, 0, sizeof(int), N, NULL, &event);

    // RUN ZE KERNEL
    cl::Kernel kernel(program, "task1");
    kernel.setArg(0, buffer_X);
    kernel.setArg(1, buffer_Y);
    kernel.setArg(2, buffer_W);
    kernel.setArg(3, buffer_N);
    kernel.setArg(4, buffer_Params);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(n), cl::NullRange, NULL, &event);
    event.wait();
    queue.finish();

    // read result from GPU to here
    cl_ulong time_start;
    cl_ulong time_end;
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &time_end);
    cl_int tt2 = event.getProfilingInfo(CL_PROFILING_COMMAND_START, &time_start);
    double time = time_end - time_start;

    queue.enqueueReadBuffer(buffer_W, CL_TRUE, 0, sizeof(int) * n, W, NULL, &event);

    //for (size_t i = 0; i < n; i++)
    //{
    //    std::cout << W[i] << " ";
    //}
    free(X);
    free(Y);
    free(W);
    return time;
}