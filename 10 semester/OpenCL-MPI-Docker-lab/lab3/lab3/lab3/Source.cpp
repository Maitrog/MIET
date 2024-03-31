// lab2-openCL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <CL/opencl.h>
#include <CL/cl_platform.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;
using namespace std;


#include <iostream>
#include <string>

#pragma OPENCL EXTENSION cl_amd_printf : enable
const int filter_radius = 3;

const char* src_d_boxfilter_rgba_x = "__kernel void d_boxfilter_rgba_x(__read_only  image2d_t img1,__write_only image2d_t img2, int w, int h, int r) {"
"const int scale = (r << 1) + 1;"
"const unsigned int y = get_global_id(0);"
"const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |" //Natural coordinates
"CLK_ADDRESS_CLAMP |" // Clamp to zeros
"CLK_FILTER_NEAREST;" //Don't interpolate
"if (y < h) {"
"	uint4 t = (uint4)(0,0,0,0);"
"	for (int x = 0; x <= r; x++) {"
"		int2 coord = (int2)(x, y);"
"		t += read_imageui(img1, smp, coord);"
"	}"
"	int2 coord2= (int2)(0, y);"
"	uint4 val = t;"
"	write_imageui(img2, coord2, t / scale);"
""
"	for (int x = 1; x < w; x++) {"
"		int2 coord = (int2)(x + r, y);"
"		t += read_imageui(img1, smp, coord);"
"		coord = (int2)(x - r - 1, y);"
"		t -= read_imageui(img1, smp, coord);"
"		coord2= (int2)(x, y);"
"		write_imageui(img2, coord2, t / scale);"
"	}"
"}"
""
"}\n";

const char* src_d_boxfilter_rgba_y = "__kernel void d_boxfilter_rgba_y(__read_only  image2d_t img1,__write_only image2d_t img2, int w, int h, int r) {"
"const int scale = (r << 1) + 1;"
"const unsigned int x = get_global_id(0);"
"const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |" //Natural coordinates
"CLK_ADDRESS_CLAMP |" // Clamp to zeros
"CLK_FILTER_NEAREST;" //Don't interpolate
"uint4 t = read_imageui(img1, smp, (int2)(x,0)) * r;"
""
"for (int y = 0; y < (r + 1); y++) {"
"	t += read_imageui(img1, smp, (int2)(x,y));"
"}"
""
"write_imageui(img2, (int2)(x,0), t / scale);"
""
"for (int y = 1; y < (r + 1); y++) {"
"	t += read_imageui(img1, smp, (int2)(x,y + r));"
"	t -= read_imageui(img1, smp, (int2)(x,0));"
"	write_imageui(img2, (int2)(x,y), t / scale);"
"}"
""
"for (int y = (r + 1); y < (h - r); y++) {"
"	t += read_imageui(img1, smp, (int2)(x, y + r));"
"	t -= read_imageui(img1, smp, (int2)(x, y - r - 1));"
"	write_imageui(img2, (int2)(x,y), t / scale);"
"}"
""
"for (int y = h - r; y < h; y++) {"
"	t += read_imageui(img1, smp, (int2)(x, h - 1));"
"	t -= read_imageui(img1, smp, (int2)(x, y - r - 1));"
"	write_imageui(img2, (int2)(x,y), t / scale);"
"}"
"}";

template <typename T>
cv::Mat createMat(T* data, int rows, int cols, int chs = 1) {
	// Create Mat from buffer 
	cv::Mat mat(rows, cols, CV_MAKETYPE(cv::DataType<T>::type, chs));
	memcpy(mat.data, data, rows * cols * chs * sizeof(T));
	return mat;
}

void showImage(cl_command_queue queue, cl_mem& image2, Mat& image) {
	// ***********************************************
	// 13. Копирование изображения  в память управляющего узла
	// ***********************************************
	cl_event event[5];

	size_t origin[] = { 0,0,0 }; // Defines the offset in pixels in the image from where to write.
	size_t region[] = { image.cols, image.rows, 1 }; // Size of object to be transferred
	const int size1 = image.cols * image.rows * 4;
	unsigned char* buffer_result = (unsigned char*)calloc(size1, sizeof(unsigned char));

	cl_int errcode_ret = 0;
	// read image in buffer
	errcode_ret = clEnqueueReadImage(queue, image2, CL_TRUE, origin, region, 0, 0, buffer_result, 0, NULL, &event[0]);
	if (errcode_ret != CL_SUCCESS)
	{
		throw new exception("Error to read from image2");
	}
	// write image to cv::mat
	Mat image_result = createMat<unsigned char>(buffer_result, image.rows, image.cols, 4);
	namedWindow("Display window result", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window result", image_result);                   // Show our image inside it.
	waitKey(0);

	if (buffer_result) free(buffer_result);
}

cl_ulong getTime(cl_event time_event) {
	cl_ulong time_start;
	cl_ulong time_end;

	clGetEventProfilingInfo(time_event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(time_event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

	return time_end - time_start;
}

cl_ulong rgbdBoxFilterX(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem& image1, cl_mem& image2, int r) {
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
	size_t source_size = strlen(src_d_boxfilter_rgba_x);
	cl_program program = clCreateProgramWithSource(context, 1, &src_d_boxfilter_rgba_x, (const size_t*)&source_size, &errcode_ret);
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
	errcode_ret = clSetKernelArg(kernel, 2, sizeof(image.cols), (void*)&image.cols);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 3, sizeof(image.rows), (void*)&image.rows);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 4, sizeof(r), (void*)&r);
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
}

cl_ulong rgbdBoxFilterY(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem& image1, cl_mem& image2, int r) {
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
	size_t source_size = strlen(src_d_boxfilter_rgba_y);
	cl_program program = clCreateProgramWithSource(context, 1, &src_d_boxfilter_rgba_y, (const size_t*)&source_size, &errcode_ret);
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
	errcode_ret = clSetKernelArg(kernel, 0, sizeof(image1), (void*)&image1);
	if (errcode_ret != CL_SUCCESS) {

		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 1, sizeof(image2), (void*)&image2);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 2, sizeof(image.cols), (void*)&image.cols);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 3, sizeof(image.rows), (void*)&image.rows);
	if (errcode_ret != CL_SUCCESS) {
		throw new exception("Error to set kernel arg");
	}
	errcode_ret = clSetKernelArg(kernel, 4, sizeof(r), (void*)&r);
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

void rgbdBoxFilter(cl_context& context, cl_device_id& deviceID, Mat& image, cl_image_format img_fmt, unsigned char* buffer, int r) {
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
	
	image3 = clCreateImage(context, CL_MEM_READ_WRITE, &img_fmt, &desc, NULL, &errcode_ret);
	if (errcode_ret != CL_SUCCESS) {
		printf("Cannon CreateImage for result\n");
		return;
	}

	cl_ulong x_time = rgbdBoxFilterX(context, deviceID, image, image1, image2, r);

	cl_ulong y_time = rgbdBoxFilterY(context, deviceID, image, image2, image3, r);
	cl_ulong result_time= (x_time + y_time) / 1000;

	printf("time: %lu\n", result_time);
}

int main()
{

	// ***********************************************
	// чтение изображения
	//  Create Image data formate
	// ***********************************************
	Mat image;
	image = imread("D:\\MIET\\10 semester\\OpenCL-MPI-Docker-lab\\lab2\\lab2\\forest.bmp", IMREAD_COLOR);   // Read the file
	//image = imread("C:\\Users\\Mihay\\Desktop\\test.bmp", IMREAD_COLOR);   // Read the file
	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.
	waitKey(0);


	// чтение типа изображения
	int image_type = image.type();
	uchar depth = ((image_type)&CV_MAT_DEPTH_MASK);
	uchar chans = ((((image_type)&CV_MAT_CN_MASK) >> CV_CN_SHIFT) + 1);

	// преобразование в формат типа изображения в формат OpenCL
	cl_image_format img_fmt;
	img_fmt.image_channel_order = CL_RGB;
	img_fmt.image_channel_data_type = CL_UNSIGNED_INT8;

	string r, a;
	switch (depth) {
	case CV_8U:  img_fmt.image_channel_data_type = CL_UNSIGNED_INT8;   r = "CV_8U"; break;
	case CV_8S:  img_fmt.image_channel_data_type = CL_SIGNED_INT8;    r = "CV_8S"; break;
	case CV_16U: img_fmt.image_channel_data_type = CL_UNSIGNED_INT16;   r = "CV_16U";  break;
	case CV_16S: img_fmt.image_channel_data_type = CL_SIGNED_INT16;   r = "CV_16S";  break;
	case CV_32S: img_fmt.image_channel_data_type = CL_SIGNED_INT32;   r = "CV_32S";  break;
	case CV_32F: img_fmt.image_channel_data_type = CL_FLOAT;   r = "CV_32F"; break;
	case CV_64F: img_fmt.image_channel_data_type = CL_FLOAT;   r = "CV_64F"; break;
	default:     img_fmt.image_channel_data_type = CL_UNSIGNED_INT8;  r = "CV_8U"; break;
	}
	switch (chans) {
	case 1: img_fmt.image_channel_order = CL_INTENSITY; break;
	case 2: img_fmt.image_channel_order = CL_RG; break;
	case 3: img_fmt.image_channel_order = CL_RGB; break;
	case 4: img_fmt.image_channel_order = CL_RGBA; break;
	default:img_fmt.image_channel_order = CL_RGBA; break;
	}
	r += "C";
	r += (chans + '0');
	cout << "Mat is of type " << r << " and should be accessed with " << a << endl;
	cout << "Mat size is: cols " << image.cols << " rows " << image.rows << " total " << image.total() << endl;


	// копирование изображение в буфер
	// копирование изображение в буфер
	const int size = image.cols * image.rows * 4;
	unsigned char* buffer = (unsigned char*)calloc(size, sizeof(unsigned char));
	for (int i = 0; i < image.cols; ++i) {
		for (int j = 0; j < image.rows; ++j) {
			for (int k = 0; k < chans; ++k) {
				buffer[4 * (j * image.cols + i) + k] = image.data[chans * (j * image.cols + i) + k];
			}
		}
	}

	// ***********************************************
	// 1. Получение платформы
	// ***********************************************
	cl_uint uNumPlatforms;
	clGetPlatformIDs(0, NULL, &uNumPlatforms);
	std::cout << uNumPlatforms << " platforms" << std::endl;
	cl_platform_id* pPlatforms = new cl_platform_id[uNumPlatforms];
	clGetPlatformIDs(uNumPlatforms, pPlatforms, &uNumPlatforms);
	// ***********************************************
	// 2. Получение информации о платформе
	// ***********************************************
	const size_t	string_size = 128;
	char			param_value[string_size] = { 0 };
	size_t 			param_value_size_ret = 0;
	for (int i = 0; i < uNumPlatforms; ++i)
	{
		cl_int res = clGetPlatformInfo(pPlatforms[i], CL_PLATFORM_NAME, string_size, static_cast<void*>(param_value), &param_value_size_ret);
		printf("Platform %i name is %s\n", pPlatforms[i], param_value);
		param_value_size_ret = 0;
	}
	// ***********************************************
	// 3. Получение номера CL устройства
	// ***********************************************
	int32_t		platform_id = 0;
	if (uNumPlatforms > 1)
	{
		platform_id = 1;
	}
	cl_device_id deviceID;
	cl_uint uNumGPU;
	clGetDeviceIDs(pPlatforms[platform_id], CL_DEVICE_TYPE_DEFAULT/*CL_DEVICE_TYPE_GPU*/, 1, &deviceID, &uNumGPU);
	// ***********************************************
	// 4. Получение информации о CL устройстве
	// ***********************************************
	param_value_size_ret = 0;
	cl_int res1 = clGetDeviceInfo(deviceID, CL_DEVICE_NAME, size, static_cast<void*>(param_value), &param_value_size_ret);
	printf("Device %i name is %s\n", deviceID, param_value);
	// ***********************************************
	// 5. Создание контекста
	// ***********************************************
	cl_int errcode_ret;
	cl_context context = clCreateContext(NULL, 1, &deviceID, NULL, NULL, &errcode_ret);
	if (errcode_ret != CL_SUCCESS) {
		printf("Error to create context");
		return 0;
	}

	errcode_ret = 0;

	cl_mem image1, image2;
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
		return 0;
	}

	image2 = clCreateImage(context, CL_MEM_READ_WRITE, &img_fmt, &desc, NULL, &errcode_ret);
	if (errcode_ret != CL_SUCCESS) {
		printf("Cannon CreateImage for result\n");
		return 0;
	}

	for(int i = 2; i <= 16; i++)
	rgbdBoxFilter(context, deviceID, image, img_fmt, buffer, i);

	// ***********************************************
	// 15. Удаление объектов и освобождение памяти 
	// управляющего узла
	// ***********************************************
	if (buffer) free(buffer);
	clReleaseContext(context);
	delete[] pPlatforms;
	return  0;
} // main()
