// Includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _WIN32
#define WINDOWS_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

// Includes CUDA
#include <cuda_runtime.h>

// Utilities and timing functions
#include <helper_functions.h>  // includes cuda.h and cuda_runtime_api.h
#include <helper_math.h>

// CUDA helper functions
#include <helper_cuda.h>  // helper functions for CUDA error check

#define MAX_EPSILON_ERROR 5e-3f

// Define the files that are to be save and the reference images for validation
//const char *imageFilename = "teapot512.pgm";
//const char* imageFilename = "dwsample-ppm-1920.ppm";
const char* imageFilename = "teapot1024.ppm";

const char* sampleName = "simpleTexture";

////////////////////////////////////////////////////////////////////////////////
// Constants
int iterations = 1;
double filter_sigma = 0.84089642; // при увеличении сигма усиливается блюр, но надо повышать яркость пикселей, можно умножать на константу в d_gaussianfilter_rgba_x (line 200) константу подбирать надо вручную (наверное существуют методы нормализации)
//double filter_sigma = 10.0;
int gaussian_radius = 3; // радиус больше делать нет смысла
int nthreads = 64;
unsigned int width, height;
unsigned int* h_img = NULL;
unsigned int* d_img = NULL;
unsigned int* d_temp = NULL;
double* gaussian_matrix = NULL;
cudaArray* d_array, * d_tempArray;
cudaTextureObject_t tex;
cudaTextureObject_t texTempArray;
cudaTextureObject_t rgbaTex;
cudaTextureObject_t rgbaTexTempArray;

void loadImageData(int argc, char** argv) {
    // load image (needed so we can get the width and height before we create the
    // window
    char* image_path = NULL;

    if (argc >= 1) {
        image_path = sdkFindFilePath(imageFilename, argv[0]);
    }

    if (image_path == 0) {
        printf("Error finding image file '%s'\n", imageFilename);
        exit(EXIT_FAILURE);
    }

    sdkLoadPPM4(image_path, (unsigned char**)&h_img, &width, &height);

    if (!h_img) {
        printf("Error opening file '%s'\n", image_path);
        exit(EXIT_FAILURE);
    }

    printf("Loaded '%s', %d x %d pixels\n", image_path, width, height);
}

extern "C" void initTexture(int width, int height, void* pImage) {
    // copy image data to array
    cudaChannelFormatDesc channelDesc;
    channelDesc = cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsigned);
    checkCudaErrors(cudaMallocArray(&d_array, &channelDesc, width, height));

    size_t bytesPerElem = sizeof(uchar4);
    checkCudaErrors(cudaMemcpy2DToArray(
        d_array, 0, 0, pImage, width * bytesPerElem, width * bytesPerElem, height,
        cudaMemcpyHostToDevice));

    checkCudaErrors(cudaMallocArray(&d_tempArray, &channelDesc, width, height));

    // set texture parameters
    cudaResourceDesc texRes;
    memset(&texRes, 0, sizeof(cudaResourceDesc));

    texRes.resType = cudaResourceTypeArray;
    texRes.res.array.array = d_array;

    cudaTextureDesc texDescr;
    memset(&texDescr, 0, sizeof(cudaTextureDesc));

    texDescr.normalizedCoords = false;
    texDescr.filterMode = cudaFilterModeLinear;
    texDescr.addressMode[0] = cudaAddressModeWrap;
    texDescr.addressMode[1] = cudaAddressModeWrap;
    texDescr.readMode = cudaReadModeNormalizedFloat;

    checkCudaErrors(cudaCreateTextureObject(&rgbaTex, &texRes, &texDescr, NULL));

    memset(&texRes, 0, sizeof(cudaResourceDesc));

    texRes.resType = cudaResourceTypeArray;
    texRes.res.array.array = d_tempArray;

    memset(&texDescr, 0, sizeof(cudaTextureDesc));

    texDescr.normalizedCoords = false;
    texDescr.filterMode = cudaFilterModeLinear;
    texDescr.addressMode[0] = cudaAddressModeClamp;
    texDescr.addressMode[1] = cudaAddressModeClamp;
    texDescr.readMode = cudaReadModeNormalizedFloat;

    checkCudaErrors(
        cudaCreateTextureObject(&rgbaTexTempArray, &texRes, &texDescr, NULL));

    memset(&texRes, 0, sizeof(cudaResourceDesc));

    texRes.resType = cudaResourceTypeArray;
    texRes.res.array.array = d_array;

    memset(&texDescr, 0, sizeof(cudaTextureDesc));

    texDescr.normalizedCoords = true;
    texDescr.filterMode = cudaFilterModePoint;
    texDescr.addressMode[0] = cudaAddressModeWrap;
    texDescr.addressMode[1] = cudaAddressModeWrap;
    texDescr.readMode = cudaReadModeElementType;

    checkCudaErrors(cudaCreateTextureObject(&tex, &texRes, &texDescr, NULL));

    memset(&texRes, 0, sizeof(cudaResourceDesc));

    texRes.resType = cudaResourceTypeArray;
    texRes.res.array.array = d_tempArray;

    memset(&texDescr, 0, sizeof(cudaTextureDesc));

    texDescr.normalizedCoords = true;
    texDescr.filterMode = cudaFilterModePoint;
    texDescr.addressMode[0] = cudaAddressModeWrap;
    texDescr.addressMode[1] = cudaAddressModeWrap;
    texDescr.readMode = cudaReadModeElementType;

    checkCudaErrors(
        cudaCreateTextureObject(&texTempArray, &texRes, &texDescr, NULL));
}

extern "C" void freeTextures() {
    checkCudaErrors(cudaDestroyTextureObject(tex));
    checkCudaErrors(cudaDestroyTextureObject(texTempArray));
    checkCudaErrors(cudaDestroyTextureObject(rgbaTex));
    checkCudaErrors(cudaDestroyTextureObject(rgbaTexTempArray));
    checkCudaErrors(cudaFreeArray(d_array));
    checkCudaErrors(cudaFreeArray(d_tempArray));
}

// RGBA version
// reads from 32-bit unsigned int array holding 8-bit RGBA

// convert floating point rgba color to 32-bit integer
__device__ unsigned int rgbaFloatToInt(float4 rgba) {
    rgba.x = __saturatef(rgba.x);  // clamp to [0.0, 1.0]
    rgba.y = __saturatef(rgba.y);
    rgba.z = __saturatef(rgba.z);
    rgba.w = __saturatef(rgba.w);
    return ((unsigned int)(rgba.w * 255.0f) << 24) |
        ((unsigned int)(rgba.z * 255.0f) << 16) |
        ((unsigned int)(rgba.y * 255.0f) << 8) |
        ((unsigned int)(rgba.x * 255.0f));
}

__device__ float4 rgbaIntToFloat(unsigned int c) {
    float4 rgba;
    rgba.x = (c & 0xff) * 0.003921568627f;          //  /255.0f;
    rgba.y = ((c >> 8) & 0xff) * 0.003921568627f;   //  /255.0f;
    rgba.z = ((c >> 16) & 0xff) * 0.003921568627f;  //  /255.0f;
    rgba.w = ((c >> 24) & 0xff) * 0.003921568627f;  //  /255.0f;
    return rgba;
}


// row pass using texture lookups
__global__ void d_gaussianfilter_rgba_x(unsigned int* od, int w, int h, int r, double* gaussian_matrix, cudaTextureObject_t rgbaTex) {
    unsigned int y = blockIdx.x * blockDim.x + threadIdx.x;
    int gaussian_m_w = (r << 1) + 1;

    // as long as address is always less than height, we do work
    if (y < h) {

        for (int x = 0; x < w; x++) {
            float4 t = make_float4(0.0f);
            for (int xx = -r; xx <= r; xx++) {
                for (int yy = -r; yy <= r; yy++) {
                    t += tex2D<float4>(rgbaTex, x + xx, y + yy) * gaussian_matrix[(xx + r) * gaussian_m_w + (yy + r)];
                }
            }

            od[y * w + x] = rgbaFloatToInt(t);
        }
    }
}

__global__ void init_gaussian_matrix(double sigma, int r, double* gaussianMatrix) {
    int x = threadIdx.x;
    int y = threadIdx.y;
    int g_x = x - r;
    int g_y = y - r;
    int g_x2 = pow(g_x, 2);
    int g_y2 = pow(g_y, 2);
    double s2 = pow(sigma, 2);
    int width = (r << 1) + 1;

    gaussianMatrix[x * width + y] = 1.0 / (2.0 * M_PI * s2) * (1.0 / pow(M_E, (double)(g_x2 + g_y2) / (2.0 * s2)));
}

extern "C" double gaussianFilterRGBA(unsigned int* d_src,
    unsigned int* d_dest, int width, int height,
    double sigma, int nthreads, int r, double* gaussian_matrix) {
    // var for kernel computation timing
    double dKernelTime;
    int gaussian_m_w = (r << 1) + 1;

    // sync host and start kernel computation timer_kernel
    dKernelTime = 0.0;
    checkCudaErrors(cudaDeviceSynchronize());

    init_gaussian_matrix << <1, dim3(gaussian_m_w, gaussian_m_w) >> > (sigma, r, gaussian_matrix);
    checkCudaErrors(cudaDeviceSynchronize());

    // use texture for horizontal pass
    d_gaussianfilter_rgba_x << <height / nthreads, nthreads, 0 >> > (d_dest, width, height, r, gaussian_matrix, rgbaTex);


    // sync host and stop computation timer_kernel
    checkCudaErrors(cudaDeviceSynchronize());

    return ((dKernelTime / 1000.) / (double)iterations);
}
////////////////////////////////////////////////////////////////////////////////
// Declaration, forward
void runTest();

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
    char* ref_file = NULL;
    printf("%s starting...\n", sampleName);

    // Process command-line arguments
    if (argc > 1) {
        if (checkCmdLineFlag(argc, (const char**)argv, "threads")) {
            nthreads = getCmdLineArgumentInt(argc, (const char**)argv, "threads");
        }

        if (checkCmdLineFlag(argc, (const char**)argv, "radius")) {
            filter_sigma =
                getCmdLineArgumentInt(argc, (const char**)argv, "radius");
        }

        if (checkCmdLineFlag(argc, (const char**)argv, "passes")) {
            iterations = getCmdLineArgumentInt(argc, (const char**)argv, "passes");
        }

        if (checkCmdLineFlag(argc, (const char**)argv, "file")) {
            getCmdLineArgumentString(argc, (const char**)argv, "file",
                (char**)&ref_file);
        }
    }

    loadImageData(argc, argv);

    runTest();
}

////////////////////////////////////////////////////////////////////////////////
//! Run a simple test for CUDA
////////////////////////////////////////////////////////////////////////////////
void runTest() {
    char dump_file[256];
    int gaussian_m_w = (gaussian_radius < 1) + 1;
    checkCudaErrors(cudaMalloc((void**)&d_img, (width * height * sizeof(unsigned int))));
    checkCudaErrors(cudaMalloc((void**)&d_temp, (width * height * sizeof(unsigned int))));
    checkCudaErrors(cudaMalloc((void**)&gaussian_matrix, (gaussian_m_w * gaussian_m_w * sizeof(double))));

    initTexture(width, height, h_img);

    unsigned int* d_result;
    unsigned int* h_result = (unsigned int*)malloc(width * height * sizeof(unsigned int));
    checkCudaErrors(cudaMalloc((void**)&d_result, width * height * sizeof(unsigned int)));

    // run the sample radius
    {
        gaussianFilterRGBA(d_img, d_result, width, height, filter_sigma, nthreads, gaussian_radius, gaussian_matrix);

        // check if kernel execution generated an error
        getLastCudaError("Error: boxFilterRGBA Kernel execution FAILED");
        checkCudaErrors(cudaDeviceSynchronize());

        // readback the results to system memory
        cudaMemcpy((unsigned char*)h_result, (unsigned char*)d_result,
            width * height * sizeof(unsigned int), cudaMemcpyDeviceToHost);

        sprintf(dump_file, "out_gaussian_%d.ppm", gaussian_radius);

        sdkSavePPM4ub((const char*)dump_file, (unsigned char*)h_result, width,
            height);

        printf("Image is convert");
    }
    printf("\n");

    free(h_result);
    checkCudaErrors(cudaFree(d_result));
}
