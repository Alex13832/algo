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
* @param[in] ImageIn, input image that is to be convoluted
* @param[in] filter_type, the chosen filter to use
* @param[in] dim, dimension of NxN filter
*/
void convolve(uint8_t* Im, uint8_t* data, int rows, int cols, filter_t filter_type, int dim);



#endif /* IMAGE_PROCESSING_H */
