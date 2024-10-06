#pragma once
#include "rgbaBoxFilter.h"

cl_ulong rgbdBoxFilterXArray(cl_context& context, cl_device_id& deviceID, Mat& image, unsigned char* buffer, int r);

cl_ulong rgbdBoxFilterYArray(cl_context& context, cl_device_id& deviceID, Mat& image, unsigned char* buffer, int r);

void rgbdBoxFilterArray(cl_context& context, cl_device_id& deviceID, Mat& image, cl_image_format img_fmt, unsigned char* buffer, int r);