#include "image_processing.h"
#include <climits>
#include <iostream>
#include <cmath>

using namespace std;

/* Filters */
float sobel_x[9]     = {-1.0/2.0, 0, 1.0/2.0, -2.0/2.0, 0, 2.0/2.0, -1.0/2.0, 0, 1.0/2.0 };
float sobel_y[9]     = {-1.0/2.0, -2.0/2.0, -1.0/2.0, 0, 0, 0, 1.0/2.0, 2.0/2.0, 1.0/2.0 };
float edge_detect[9] = {-1.0, -1.0, -1.0, -1.0, 8.0, -1.0, -1.0, -1.0, -1.0};
float smoothing[9]   = {1.0/13.0, 2.0/13.0, 1.0/13.0, 2.0/13.0, 4.0/13.0, 2.0/13.0, 1.0/13.0, 2.0/13.0, 1.0/13.0};
float sharp_agg[9]   = {0, -1.0, 0, -1.0, 5.0, -1.0, 0, -1.0, 0};
float sharp_mod[9]   = {-1.0/9.0, -1.0/9.0, -1.0/9.0, -1.0/9.0, 17.0/9.0, -1.0/9.0, -1.0/9.0, -1.0/9.0, -1.0/9.0};
float g_blur[9]      = {1.0/16.0, 2.0/16.0, 1.0/16.0, 2.0/16.0, 5.0/16.0, 2.0/16.0, 1.0/16.0, 2.0/16.0, 1.0/16.0};
float blur_hard[9]   = {1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0};
float blur_soft[9]   = {0.0, 1.0/8.0, 0.0, 1.0/8.0, 1.0/2.0, 1.0/8.0, 0.0, 1.0/8.0, 0.0};
float emboss[9]      = {-2.0, -1.0, 0.0, -1.0, 1.0, 1.0, 0.0, 1.0, 2.0};
float weighted[9]    = {1.0/16.0, 2.0/16.0, 1.0/16.0, 2.0/16.0, 4.0/16.0, 2.0/16.0, 1.0/16.0, 2.0/16.0, 1.0/16.0};
float dil_vert[9]    = {0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0};
float dil_hor[9]     = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
float dilation[9]    = {0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0};
float high_pass[9]   = {-1.0, -1.0, -1.0, -1.0, 8.0, -1.0, -1.0, -1.0, -1.0};


const float* get_filter(filter_t filter_type)
{
    switch (filter_type) {
        case SOBEL_X:
            return sobel_x;
        case SOBEL_Y:
            return sobel_y;
        case EDGE_DETECT:
            return edge_detect;
        case SMOOTHING:
            return smoothing;
        case SHARPEN_MODEST:
            return sharp_mod;
        case SHARPEN_AGGRESSIVE:
            return sharp_agg;
        case GAUSSIAN_BLUR:
            return g_blur;
        case BLUR_HARD:
            return blur_hard;
        case BLUR_SOFT:
            return blur_soft;
        case EMBOSS:
            return emboss;
        case WEIGHTED_AVERAGE:
            return weighted;
        case DILATION_VERTICAL:
            return dil_vert;
        case DILATION_HORIZONTAL:
            return dil_hor;
        case DILATION:
            return dilation;
        case HIGH_PASS:
            return high_pass;

    }

    return NULL;
}

vector<uint8_t> convolve(  const vector<uint8_t> Im,const unsigned rows, const unsigned cols,
                                filter_t filter_type, unsigned dim)
{
    int i, j, k, m;
    int sz = dim>>1;

    const float* filter = get_filter(filter_type);

    // Output pixels
    vector<uint8_t> data(rows*cols,0);

    // Filtering window
    for(i=sz; i < rows-sz; i++) {
		for(j=sz; j < cols-sz; j++) {
			float sum = 0;
			for(k=0; k<dim; k++) {
				for(m=0; m<dim; m++) {
                    // Multiply components
                    float im_num = (float)(Im[(i+k-sz)*cols+(j+m-sz)]);
                    float filt_num = filter[k*dim+m];
					sum += im_num*filt_num;
				}
			}

            // Check overflow
            if (sum < 0) sum = 0;
            if (sum > 255) sum = 255;

            data[i*cols + j] = (uint8_t)sum;
		}
	}

    return data;
}
