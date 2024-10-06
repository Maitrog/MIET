// lab2-openCL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <CL/opencl.h>
#include <CL/cl_platform.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "rgbaBoxFilter.h"
#include "rgbaBoxFilterArray.h"
#include "rgbaGausianFilter.h"
using namespace cv;
using namespace std;


#include <iostream>
#include <string>

#pragma OPENCL EXTENSION cl_amd_printf : enable
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
const int filter_radius = 3;

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
	/*if (uNumPlatforms > 1)
	{
		platform_id = 1;
	}*/
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

	for(int i = 3; i <= 3; i++)
	//rgbdBoxFilter(context, deviceID, image, img_fmt, buffer, i);
	rgbdGausianFilter(context, deviceID, image, img_fmt, buffer, i);

	// ***********************************************
	// 15. Удаление объектов и освобождение памяти 
	// управляющего узла
	// ***********************************************
	if (buffer) free(buffer);
	clReleaseContext(context);
	delete[] pPlatforms;
	return  0;
} // main()
