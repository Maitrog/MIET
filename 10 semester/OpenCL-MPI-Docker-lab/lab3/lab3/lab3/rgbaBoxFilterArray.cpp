#include "rgbaBoxFilterArray.h"

const char* src_d_boxfilter_rgba_x_array = "__kernel void d_boxfilter_rgba_x(__global uchar4* img1, __global uint4* img2, __constant int* params) {\n"
"const int w = params[0], h = params[1], r = params[2];\n"
"const int scale = (r << 1) + 1;\n"
"const unsigned int y = get_global_id(0);\n"
"if (y < h) {\n"
"	uint4 t = 0;\n"
"	for (int x = 0; x <= r; x++) {\n"
"		t +=  convert_uint4(img1[y * w + x]);\n"
"	}\n"
"	img2[y * w] = t / scale;\n"
"	printf(\"%d, %d, %d, %d\\n\", t.x, t.y, t.z, t.w);"
"\n"
"	for (int x = 1; x < w; x++) {\n"
"		t += convert_uint4(img1[y * w + x + r]);\n"
"		t -=  convert_uint4(img1[y * w + (x - r - 1)]);\n"
"		img2[y * w + x] =  t / scale;\n"
"	}\n"
"}\n"
"\n"
"}\n";

const char* src_d_boxfilter_rgba_y_array = "__kernel void d_boxfilter_rgba_y(__global uint4* img1,__global uchar4* img2, __constant int* params) {"
"const int w = params[0], h = params[1], r = params[2];"
"const int scale = (r << 1) + 1;"
"const unsigned int x = get_global_id(0);"
"uint4 t = img1[x] * r;"
""
"for (int y = 0; y < (r + 1); y++) {"
"	t += img1[y * w + x];"
"}"
""
"write_imageui(img2, (int2)(x,0), t / scale);"
""
"for (int y = 1; y < (r + 1); y++) {"
"	t += img1[(y + r) * w + x];"
"	t -= img1[x];"
"	img2[y * w + x] = t / scale;"
"}"
""
"for (int y = (r + 1); y < (h - r); y++) {"
"	t += img1[(y + r) * w + x];"
"	t -= img1[(y - r - 1) * w + x];"
"	img2[y * w + x] = t / scale;"
"}"
""
"for (int y = h - r; y < h; y++) {"
"	t += read_imageui(img1, smp, (int2)(x, h - 1));"
"	t += img1[( h - 1) * w + x];"
"	t -= img1[(y - r - 1) * w + x];"
"	img2[y * w + x] = t / scale;"
"}"
"}";

cl_ulong rgbdBoxFilterXArray(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem image1, cl_mem image2, unsigned char* buffer, int r) {
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
	size_t source_size = strlen(src_d_boxfilter_rgba_x_array);
	cl_program program = clCreateProgramWithSource(context, 1, &src_d_boxfilter_rgba_x_array, (const size_t*)&source_size, &errcode_ret);
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
	cl_kernel kernel = clCreateKernel(program, "d_boxfilter_rgba_x", &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create Kernel");
	}

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
	errcode_ret = clSetKernelArg(kernel, 2, sizeof(d_params), (void*)&d_params);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	// ***********************************************
	// 12. Запуск ядра d_boxfilter_rgba_x
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	//const size_t global_work_size[] = { image.rows };
	size_t global_work_size = image.rows;
	cl_event time_event;

	errcode_ret = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &time_event);
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

cl_ulong rgbdBoxFilterYArray(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem image1, cl_mem image2, int r) {
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
	// 7. Создание программы d_boxfilter_rgba_y
	// ***********************************************
	size_t source_size = strlen(src_d_boxfilter_rgba_y_array);
	cl_program program = clCreateProgramWithSource(context, 1, &src_d_boxfilter_rgba_y_array, (const size_t*)&source_size, &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create program");
	}
	// ***********************************************
	// 8. Сборка программы d_boxfilter_rgba_y
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
	// 9. Получение ядра d_boxfilter_rgba_y
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	cl_kernel kernel = clCreateKernel(program, "d_boxfilter_rgba_y", &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to create Kernel");
	}

	// ***********************************************
	// 11. Установка изображения в качестве аргумента ядра d_boxfilter_rgba_y
	// ***********************************************
	int params[3] = { image.cols, image.rows, r };
	cl_mem d_params = clCreateBuffer(context, CL_MEM_READ_ONLY, 3 * sizeof(int), NULL, NULL);
	clEnqueueWriteBuffer(queue, d_params, CL_TRUE, 0, 3 * sizeof(int), params, 0, NULL, NULL);

	errcode_ret = clSetKernelArg(kernel, 0, sizeof(image1), (void*)&image1);
	if (errcode_ret != CL_SUCCESS) {

		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 1, sizeof(image2), (void*)&image2);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 2, sizeof(d_params), &d_params);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	// ***********************************************
	// 12. Запуск ядра d_boxfilter_rgba_y
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	//const size_t global_work_size[] = { image.cols };
	size_t global_work_size = image.cols;
	cl_event time_event;

	errcode_ret = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &time_event);
	clFinish(queue);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error in EnqueueNDRangeKernel");
	}

	cl_ulong nanoSeconds = getTime(time_event);

	//showImage(queue, image2, image);

	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);

	return nanoSeconds;
}

void rgbdBoxFilterArray(cl_context& context, cl_device_id& deviceID, Mat& image, cl_image_format img_fmt, unsigned char* buffer, int r) {
	cl_int errcode_ret = CL_SUCCESS;
	cl_mem image1, image2, image3;
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
	const int size = image.cols * image.rows * 4;
	image1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, size * sizeof(unsigned char), buffer, NULL);
	image2 = clCreateBuffer(context, CL_MEM_READ_WRITE, size * sizeof(uint), NULL, NULL);
	image3 = clCreateBuffer(context, CL_MEM_READ_WRITE, size * sizeof(unsigned char), NULL, NULL);

	cl_ulong x_time = rgbdBoxFilterXArray(context, deviceID, image, image1, image2, buffer, r);

	cl_ulong y_time = rgbdBoxFilterYArray(context, deviceID, image, image2, image3, r);
	cl_ulong result_time = (x_time + y_time) / 1000;

	printf("time: %lu\n", result_time);
}