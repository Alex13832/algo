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

/**
* Median filter for noise removal in Im, returns the result in data;
* @param[in] Im, input image with noise,
* @param[out] data, result
* @param[in] rows, #rows in Im
* @param[in] cols, #columns in Im
*/
void median_filter(uint8_t* Im, uint8_t* data, const int rows, const int cols);

/**
* Instead of choosing the median value, here the value can be changed. If a median
* filter is to be used then rank == 4.
* @param[in] Im, input image with noise,
* @param[out] data, result
* @param[in] rows, #rows in Im
* @param[in] cols, #columns in Im
*/
void rank_filter(uint8_t* Im, uint8_t* data, const int rows, const int cols, int rank);

/**
* Detects difference between ImRef and ImComp and returns the result in diff.
* @param[in] ImRef, reference image,
* @param[in] ImRef, image with difference, note that it should have same
*                   background as ImRef
* @param[out] diff, detected difference
* @param[in] rows, #rows in ImRef/ImComp
* @param[in] cols, #columns in ImRef/ImComp
*/
void detect_diff(uint8_t* ImRef, uint8_t* ImComp, uint8_t* diff, const int rows, const int cols);

/**
* Template matching algorithm, finds a point where the intesity values meet
* in the image Im and the template image templ. Note that the speed of computation
* highly depends on the template size.
* @param[in] Im, reference image,
* @param[in] im_rows, #rows in the reference image,
* @param[in] im_cols, #cols -           "          -
* @param[in] templ, template image,
* @param[in] r_rows and t_cols, #cols and #rows in the template
* @param[out] besti and bestj, best point where template and reference match.
*/
void template_match( uint8_t* Im, int im_rows, int im_cols,
                uint8_t* templ, int t_rows, int t_cols,
                int* bestj, int* besti);

#endif /* IMAGE_PROCESSING_H */
