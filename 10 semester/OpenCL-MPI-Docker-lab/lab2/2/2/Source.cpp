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

// негатив
//const char* src_img_test = "__kernel void imgTeste(__read_only  image2d_t img1,__write_only image2d_t img2) {"
//"const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |" //Natural coordinates
//"CLK_ADDRESS_CLAMP |" // Clamp to zeros
//"CLK_FILTER_NEAREST;" //Don't interpolate
//"int2 coord = (int2)(get_global_id(0), get_global_id(1));\n"
//"uint4 val = read_imageui(img1, smp, coord);\n"
//"val.y = 255-val.y;"
//"val.z = 255-val.z;"
//"val.x = 255-val.x;"
//"write_imageui(img2, coord, val);\n }\n";


// чб изображение
const char* src_img_test = "__kernel void imgTeste(__read_only  image2d_t img1,__write_only image2d_t img2) {"
"const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |" //Natural coordinates
"CLK_ADDRESS_CLAMP |" // Clamp to zeros
"CLK_FILTER_NEAREST;" //Don't interpolate
"int2 coord = (int2)(get_global_id(0), get_global_id(1));\n"
"uint4 val = read_imageui(img1, smp, coord);\n"
"int avg = (val.y + val.z + val.x) / 3;"
"val.y = avg;"
"val.z = avg;"
"val.x = avg;"
"write_imageui(img2, coord, val);\n }\n";

template <typename T>
cv::Mat createMat(T* data, int rows, int cols, int chs = 1) {
	// Create Mat from buffer 
	cv::Mat mat(rows, cols, CV_MAKETYPE(cv::DataType<T>::type, chs));
	memcpy(mat.data, data, rows * cols * chs * sizeof(T));
	return mat;
}

int main()
{

	// ***********************************************
	// чтение изображения
	//  Create Image data formate
	// ***********************************************
	Mat image;
	image = imread("D:\\MIET\\10 semester\\OpenCL-MPI-Docker-lab\\lab2\\lab2\\forest.bmp", IMREAD_COLOR);   // Read the file
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


	// ***********************************************
	// 6. Создание очереди команд
	// ***********************************************
	errcode_ret = 0;
	cl_queue_properties qprop[] = {
		CL_QUEUE_PROPERTIES,
		(cl_command_queue_properties)CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE , 0 };


	cl_command_queue queue = clCreateCommandQueueWithProperties(context, deviceID, qprop, &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		printf("Error to create command queue");
		return 0;
	}


	// ***********************************************
	// 7. Создание программы
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	size_t source_size = strlen(src_img_test);
	cl_program program = clCreateProgramWithSource(context, 1, &src_img_test, (const size_t*)&source_size, &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		printf("Error to create program");
		return 0;
	}
	// ***********************************************
	// 8. Сборка программы
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

		printf("Error to build program");
		return 0;
	}
	// ***********************************************
	// 9. Получение ядра
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	cl_kernel kernel = clCreateKernel(program, "imgTeste", &errcode_ret);
	if (errcode_ret != CL_SUCCESS)
	{
		printf("Error to create Kernel");
		return 0;
	}

	// ***********************************************
	// 10. Создание избражения
	// ***********************************************

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


	// ***********************************************
	// 11. Установка изображения в качестве аргумента ядра
	// ***********************************************
	errcode_ret = clSetKernelArg(kernel, 0, sizeof(image1), (void*)&image1);
	if (errcode_ret != CL_SUCCESS) {

		printf("Error to set kernel arg");
		return 0;
	}
	errcode_ret = clSetKernelArg(kernel, 1, sizeof(image2), (void*)&image2);
	if (errcode_ret != CL_SUCCESS) {
		printf("Error to set kernel arg");
		return 0;
	}
	// ***********************************************
	// 12. Запуск ядра
	// ***********************************************
	errcode_ret = CL_SUCCESS;
	const size_t global_work_size[] = { image.cols, image.rows };

	errcode_ret = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
	clFinish(queue);
	if (errcode_ret != CL_SUCCESS) {

		printf("Error шт EnqueueNDRangeKernel");
		return 0;
	}
	// ***********************************************
	// 13. Копирование изображения  в память управляющего узла
	// ***********************************************
	cl_event event[5];

	size_t origin[] = { 0,0,0 }; // Defines the offset in pixels in the image from where to write.
	size_t region[] = { image.cols, image.rows, 1 }; // Size of object to be transferred
	const int size1 = image.cols * image.rows * 4;
	unsigned char* buffer_result = (unsigned char*)calloc(size1, sizeof(unsigned char));

	errcode_ret = 0;
	// read image in buffer
	errcode_ret = clEnqueueReadImage(queue, image2, CL_TRUE, origin, region, 0, 0, buffer_result, 0, NULL, &event[0]);
	if (errcode_ret != CL_SUCCESS)
	{
		printf("Error to create context");
		return 0;
	}
	// write image to cv::mat
	Mat image_result = createMat<unsigned char>(buffer_result, image.rows, image.cols, 4);
	// ***********************************************
	// 14. Использование результатов
	// ***********************************************
	errcode_ret = CL_SUCCESS;

	namedWindow("Display window result", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window result", image_result);                   // Show our image inside it.

	waitKey(0);


	// ***********************************************
	// 15. Удаление объектов и освобождение памяти 
	// управляющего узла
	// ***********************************************
	if (buffer) free(buffer);
	if (buffer_result) free(buffer_result);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	delete[] pPlatforms;
	return  0;
} // main()
