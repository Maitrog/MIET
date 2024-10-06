#include "rgbaGausianFilter.h"
#ifndef __OPENCL_C_VERSION__
#include <cmath>
#endif

const double filter_sigma = 0.84089642;
const char* src_d_gausianfilter_rgba_local = "__kernel void d_gausianfilter_rgba(__read_only image2d_t img1,__write_only image2d_t img2, __constant double* gaussian_matrix, __constant int* params, __local double* g_m) {\n"
"const int w = params[0], h = params[1], r = params[2];\n"
//"const unsigned int y = get_global_id(0);"
"const int gaussian_m_w = (r << 1) + 1;\n"
"const int y = get_global_id(0) + get_global_id(1) * 64;\n"
"const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |" //Natural coordinates
"CLK_ADDRESS_CLAMP |" // Clamp to zeros
"CLK_FILTER_NEAREST;\n" //Don't interpolate
"int size = (r << 1) + 1;\n"
"int g = get_global_id(0);\n"
"if (g < size * size) {\n"
"g_m[g] = gaussian_matrix[g];"
"}\n"
"barrier(CLK_LOCAL_MEM_FENCE);\n"
"if (y < h) {\n"
"	for (int x = 0; x < w; x++) {\n"
"		uint4 t = 0;\n"
"		for (int xx = -r; xx <= r; xx++) {\n"
"			for (int yy = -r; yy <= r; yy++) {"
"				int2 coord = (int2)(x + xx, y + yy);\n"
"				int scale = 1.0 /  g_m[(xx + r) * gaussian_m_w + (yy + r)];\n"
"				t += read_imageui(img1, smp, coord) / scale;\n"
"			}\n"
"		}\n"
"		int2 coord2 = (int2)(x, y);\n"
"		write_imageui(img2, coord2, t);\n"
"	}\n"
"}\n"
""
"}\n";

const char* src_d_gausianfilter_rgba = "__kernel void d_gausianfilter_rgba(__read_only image2d_t img1,__write_only image2d_t img2, __constant double* gaussian_matrix, __constant int* params) {\n"
"const int w = params[0], h = params[1], r = params[2];\n"
//"const unsigned int y = get_global_id(0);"
"const int gaussian_m_w = (r << 1) + 1;\n"
"const int y = get_global_id(0) + get_global_id(1) * 64;\n"
"const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |" //Natural coordinates
"CLK_ADDRESS_CLAMP |" // Clamp to zeros
"CLK_FILTER_NEAREST;\n" //Don't interpolate
"if (y < h) {\n"
"	for (int x = 0; x < w; x++) {\n"
"		uint4 t = 0;\n"
"		for (int xx = -r; xx <= r; xx++) {\n"
"			for (int yy = -r; yy <= r; yy++) {"
"				int2 coord = (int2)(x + xx, y + yy);\n"
"				int scale = 1.0 /  gaussian_matrix[(xx + r) * gaussian_m_w + (yy + r)];\n"
"				t += read_imageui(img1, smp, coord) / scale;\n"
"			}\n"
"		}\n"
"		int2 coord2 = (int2)(x, y);\n"
"		write_imageui(img2, coord2, t);\n"
"	}\n"
"}\n"
""
"}\n";

const char* src_d_gausianmatrix = "__kernel void d_gausianmatrix(__global double* gaussianMatrix, __constant double* params) {\n"
"const double sigma = params[0];\n"
"const int r = params[1];\n"
"int x = get_global_id(0);\n"
"int y = get_global_id(1);\n"
"float g_x = x - r;\n"
"float g_y = y - r;\n"
"float g_x2 = pow(g_x, 2);\n"
"float g_y2 = pow(g_y, 2);\n"
"double s2 = pow(sigma, 2);\n"
"int width = (r << 1) + 1;\n"
"gaussianMatrix[x * width + y] = 1.0 / (2.0 * M_PI * s2) * (1.0 / pow(M_E, (double)(g_x2 + g_y2) / (2.0 * s2)));\n"
"}";

cl_ulong kernel_rgbdGausianFilter(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem& image1, cl_mem& image2, cl_mem& gausianMatrix, int r) {
	cl_int errcode_ret = CL_SUCCESS;
	cl_queue_properties qprop[] = {
		CL_QUEUE_PROPERTIES,
		(cl_command_queue_properties)CL_QUEUE_PROFILING_ENABLE, 0 };

	cl_command_queue queue = clCreateCommandQueueWithProperties(context, deviceID, qprop, &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create command queue");
	}
	// ***********************************************
	// 7. Создание программы d_boxfilter_rgba_x
	// ***********************************************
	size_t source_size = strlen(src_d_gausianfilter_rgba_local);
	cl_program program = clCreateProgramWithSource(context, 1, &src_d_gausianfilter_rgba_local, (const size_t*)&source_size, &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create program");
	}
	// ***********************************************
	// 8. Сборка программы d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = clBuildProgram(program, 1, &deviceID, NULL, NULL, NULL);
	if (errcode_ret != CL_SUCCESS)
	{

		if (errcode_ret == CL_BUILD_PROGRAM_FAILURE) {
			// Determine the size of the log
			size_t log_size;
			clGetProgramBuildInfo(program, deviceID, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

			// Allocate memory for the log
			char* log = (char*)malloc(log_size);

			// Get the log
			clGetProgramBuildInfo(program, deviceID, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

			// Print the log
			printf("%s\n", log);
		}

		throw new exception("Error to build program");
	}
	// ***********************************************
	// 9. Получение ядра d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	cl_kernel kernel = clCreateKernel(program, "d_gausianfilter_rgba", &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create Kernel");
	}

	int g_m_size = (r << 1) + 1;
	int params[3] = { image.cols, image.rows, r };
	cl_mem d_params = clCreateBuffer(context, CL_MEM_READ_ONLY, 3 * sizeof(int), NULL, NULL);
	clEnqueueWriteBuffer(queue, d_params, CL_TRUE, 0, 3 * sizeof(int), params, 0, NULL, NULL);
	// ***********************************************
	// 11. Установка изображения в качестве аргумента ядра d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = clSetKernelArg(kernel, 0, sizeof(image1), (void*)&image1);
	if (errcode_ret != CL_SUCCESS) {

		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 1, sizeof(image2), (void*)&image2);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 2, sizeof(gausianMatrix), (void*)&gausianMatrix);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 3, sizeof(d_params), &d_params);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 4, g_m_size * g_m_size * sizeof(double), NULL);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	// ***********************************************
	// 12. Запуск ядра d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	int nthreads = 64;
	const size_t global_work_size[] = { nthreads, image.rows / nthreads };
	//size_t global_work_size = image.rows;
	cl_event time_event;

	errcode_ret = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, &time_event);
	clFinish(queue);
	if (errcode_ret != CL_SUCCESS) {

		throw new exception("Error in EnqueueNDRangeKernel");
	}
	cl_ulong nanoSeconds = getTime(time_event);

	showImage(queue, image2, image);

	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);

	return nanoSeconds;
}

cl_ulong rgbdGausianMatrix(cl_context& context, cl_device_id& deviceID, cl_mem& gausianMatrix, int r, double sigma) {
	cl_int errcode_ret = CL_SUCCESS;
	cl_queue_properties qprop[] = {
		CL_QUEUE_PROPERTIES,
		(cl_command_queue_properties)CL_QUEUE_PROFILING_ENABLE, 0 };

	cl_command_queue queue = clCreateCommandQueueWithProperties(context, deviceID, qprop, &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create command queue");
	}
	// ***********************************************
	// 7. Создание программы d_boxfilter_rgba_x
	// ***********************************************
	size_t source_size = strlen(src_d_gausianmatrix);
	cl_program program = clCreateProgramWithSource(context, 1, &src_d_gausianmatrix, (const size_t*)&source_size, &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create program");
	}
	// ***********************************************
	// 8. Сборка программы d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = clBuildProgram(program, 1, &deviceID, NULL, NULL, NULL);
	if (errcode_ret != CL_SUCCESS)
	{

		if (errcode_ret == CL_BUILD_PROGRAM_FAILURE) {
			// Determine the size of the log
			size_t log_size;
			clGetProgramBuildInfo(program, deviceID, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

			// Allocate memory for the log
			char* log = (char*)malloc(log_size);

			// Get the log
			clGetProgramBuildInfo(program, deviceID, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

			// Print the log
			printf("%s\n", log);
		}

		throw new exception("Error to build program");
	}
	// ***********************************************
	// 9. Получение ядра d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	cl_kernel kernel = clCreateKernel(program, "d_gausianmatrix", &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create Kernel");
	}

	double params[2] = { sigma, r };
	cl_mem d_params = clCreateBuffer(context, CL_MEM_READ_ONLY, 2 * sizeof(double), NULL, NULL);
	clEnqueueWriteBuffer(queue, d_params, CL_TRUE, 0, 2 * sizeof(double), params, 0, NULL, NULL);
	// ***********************************************
	// 11. Установка изображения в качестве аргумента ядра d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = clSetKernelArg(kernel, 0, sizeof(gausianMatrix), (void*)&gausianMatrix);
	if (errcode_ret != CL_SUCCESS) {

		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 1, sizeof(d_params), &d_params);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	// ***********************************************
	// 12. Запуск ядра d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	int gaussian_m_w = (r << 1) + 1;
	const size_t global_work_size[] = { gaussian_m_w, gaussian_m_w };
	cl_event time_event;

	errcode_ret = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, &time_event);
	clFinish(queue);
	if (errcode_ret != CL_SUCCESS) {

		throw new exception("Error in EnqueueNDRangeKernel");
	}
	cl_ulong nanoSeconds = getTime(time_event);


	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);

	return nanoSeconds;
}

void rgbdGausianFilter(cl_context& context, cl_device_id& deviceID, Mat& image, cl_image_format img_fmt, unsigned char* buffer, int r) {
	cl_int errcode_ret = CL_SUCCESS;
	cl_mem image1, image2, gausianMatrix;
	cl_image_desc desc;
	desc.image_type = CL_MEM_OBJECT_IMAGE2D;
	desc.image_width = image.cols;
	desc.image_height = image.rows;
	desc.image_row_pitch = 0;
	desc.image_slice_pitch = 0;
	desc.num_mip_levels = 0;
	desc.num_samples = 0;
	desc.buffer = NULL;

	img_fmt.image_channel_order = CL_RGBA;
	img_fmt.image_channel_data_type = CL_UNSIGNED_INT8;
	image1 = clCreateImage(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, &img_fmt, &desc, buffer, &errcode_ret);
	if (errcode_ret != CL_SUCCESS) {
		printf("Cannon CreateImage from host ptr");
		return;
	}

	image2 = clCreateImage(context, CL_MEM_READ_WRITE, &img_fmt, &desc, NULL, &errcode_ret);
	if (errcode_ret != CL_SUCCESS) {
		printf("Cannon CreateImage for result\n");
		return;
	}

	int gaussian_m_w = (r << 1) + 1;
	int g_size = gaussian_m_w * gaussian_m_w;
	gausianMatrix = clCreateBuffer(context, CL_MEM_READ_WRITE, g_size * sizeof(double), NULL, NULL);

	cl_ulong x_time = rgbdGausianMatrix(context, deviceID, gausianMatrix, r, filter_sigma);

	cl_ulong y_time = kernel_rgbdGausianFilter(context, deviceID, image, image1, image2, gausianMatrix, r);
	cl_ulong result_time = (x_time + y_time) / 1000;

	printf("time: %lu\n", result_time);
}