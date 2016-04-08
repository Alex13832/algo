// Image Processing library.
// The aim for this implementing this library is to implement image processing
// algorithms from scratch.
//
// Alexander Karlsson 2016-04-06

#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING


#include <stdint.h>

/* Filter types */
typedef enum filter_t {
    SOBEL_X,                // Differentation in X
    SOBEL_Y,                // Differentation in Y
    EDGE_DETECT,
    SMOOTHING,
    SHARPEN_MODEST,
    SHARPEN_AGGRESSIVE,
    GAUSSIAN_BLUR,
    BLUR_HARD,              // Low pass filter 1
    BLUR_SOFT,              // Low pass filter 2
    HIGH_PASS,
    EMBOSS,
    WEIGHTED_AVERAGE,
    DILATION_VERTICAL,
    DILATION_HORIZONTAL,
    DILATION
} filter_t;

/**
* Returns a discrete convolution of ImageIn with the Mask
* @param[in] Im, input image that is to be convoluted
* @param[out] data, output data
* @param[in] filter_type, the chosen filter to use
* @param[in] dim, dimension of NxN filter
*/
void convolve(uint8_t* Im, uint8_t* data, int rows, int cols, filter_t filter_type, int dim);

/**
* Returns an image that has been thresholded, using an adaptive approach.
* The threshold is based on the meanvalue calcualted in the regionSize^2 around
* a pixel.
* @param[in] Im, input pixels,
* @param[out] data, output pixels,
* @param[in] rows, #rows of input pixels
* @param[in] cols, #columns of input pixels
* @param[in] regionSize, the size of the area that is to be used to calculate
*           the mean value in.
* @param[in] cutWhite, 0: threshold to 0, 1: threshold to 1.
*/
void adaptive_threshold(uint8_t* Im, uint8_t* data, const int rows, const int cols,
                        const uint16_t regionSize, const int cutWhite);

void median_filter(uint8_t* Im, uint8_t* data, const int rows, const int cols);


#endif /* IMAGE_PROCESSING_H */
