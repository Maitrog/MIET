#pragma once
#include <CL/opencl.h>
#include <CL/cl_platform.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;
using namespace std;


#include <iostream>
#include <string>

void showImage(cl_command_queue queue, cl_mem& image2, Mat& image);

cl_ulong getTime(cl_event time_event);

cl_ulong rgbdBoxFilterX(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem& image1, cl_mem& image2, int r);

cl_ulong rgbdBoxFilterY(cl_context& context, cl_device_id& deviceID, Mat& image, cl_mem& image1, cl_mem& image2, int r);

void rgbdBoxFilter(cl_context& context, cl_device_id& deviceID, Mat& image, cl_image_format img_fmt, unsigned char* buffer, int r);