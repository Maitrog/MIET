#pragma once
#include "rgbaBoxFilter.h"

cl_ulong kernel_rgbdGausianFilter(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem& image1, cl_mem& image2, cl_mem& gausianMatrix, int r);

cl_ulong rgbdGausianMatrix(cl_context& context, cl_device_id& deviceID, cl_mem& gausianMatrix, int r, double sigma);

void rgbdGausianFilter(cl_context& context, cl_device_id& deviceID, Mat& image, cl_image_format img_fmt, unsigned char* buffer, int r);