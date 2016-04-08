#include "image_processing.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


void convolve(uint8_t* Im, uint8_t* data, int rows, int cols, filter_t filter_type, int dim)
{
    int i, j, k, m;
    int sz = dim>>1;

    const float* filter = get_filter(filter_type);

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
}


void adaptive_threshold(uint8_t* Im, uint8_t* data, const int rows, const int cols,
                        const uint16_t regionSize, const int cutWhite)
{
    // Check some base cases
    if (regionSize > rows) return;
    if (cutWhite < 0 || cutWhite > 1) return;

    // Input pixels
    int i, j, k, m;
    int sz = regionSize>>1;

    for(i=sz; i < rows-sz; i++) {
		for(j=sz; j < cols-sz; j++) {
			float threshold = 0;
            // Sum over the window
			for(k = 0; k < regionSize; k++) {
				for(m = 0; m < regionSize; m++) {

                    float im_num = (float)(Im[(i+k-sz)*cols+(j+m-sz)]);
					threshold += im_num;
				}
			}
            // Calculate the mean value of the window
            int mean_thresh = threshold / (float) (regionSize*regionSize);

            // Threshold pixels with respect to mean value
            uint8_t thresh = 0;
            if (cutWhite == 1) {
                if (Im[i*cols + j] > mean_thresh) thresh = 255;
                else thresh = 0;

            } else if (cutWhite == 0) {
                if (Im[i*cols + j] < mean_thresh) thresh = 255;
                else thresh = 0;
            }

            data[i*cols + j] = thresh;
		}
	}
}

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

void median_filter(uint8_t* Im, uint8_t* data, const int rows, const int cols)
{
    unsigned i, j;

    int median_vec[9];

    // Filtering window
    for(i = 1; i < rows-1; i++) {
        for(j = 1; j < cols-1; j++) {

            median_vec[0] = Im[(i-1)*cols + (j-1)];
            median_vec[1] = Im[(i-1)*cols + (j)];
            median_vec[2] = Im[(i-1)*cols + (j+1)];
            median_vec[3] = Im[(i)*cols + (j-1)];
            median_vec[4] = Im[(i)*cols + (j)];
            median_vec[5] = Im[(i)*cols + (j+1)];
            median_vec[6] = Im[(i+1)*cols + (j-1)];
            median_vec[7] = Im[(i+1)*cols + (j)];
            median_vec[8] = Im[(i+1)*cols + (j+1)];

            qsort(median_vec, 9, sizeof(int), cmpfunc);

            data[i*cols + j] = median_vec[4];
        }
    }
}
