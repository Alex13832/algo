#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING

#include <cstdint>
#include <vector>

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
std::vector<uint8_t> convolve(  const std::vector<uint8_t> Im, const unsigned rows,
                                const unsigned cols, filter_t filter_type, unsigned dim);

/**
* Returns a thresholded image. The threshold is bades on mean value in a region
* with size regionsize*regionsize. If the image should be thresholded to white
* set cutWhite to 1, otherwise to 0;
* @param[in] ImageIn, the input image
* @param[in] regionSize, the height or width (doen't matter (NxN)) of the region
* @param[in] cutWhite, if threshold should set thresholded pixels to white or black
*/
//pb_image_t* adaptive_threshold( pb_image_t* ImageIn,
//                                const uint16_t regionSize,
//                                const int cutWhite);


//pb_image_t* threshold(  pb_image_t* ImageIn,
//                        const uint8_t threshold,
//                        const int cutWhite);

//pb_image_t* polar_coordinates(pb_image_t* ImageIn);


/**
* Returns an Image manipulated with a histogram equalizer.
* @param[in] ImageIn, the input image
*/
//pb_image_t* histogram_equalization(pb_image_t* ImageIn);

//pb_image_t* rotate_image(pb_image_t* ImageIn, int angle);


#endif /* IMAGE_PROCESSING_H */
