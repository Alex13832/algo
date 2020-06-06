Image filter algorithms
==============

## Image convolutions

### Kernels

All kernels are 3x3 in size.

| Kernel type | Description | Example, gray-scale | Example, color |
|---|---|:---:|:---:|
|`SOBEL_X             ` | Horizontal edge detection.                          |![Image1](images/image_filter_sobel_x.png)           | ![Image1](images/image_filter_color_sobel_x.png)           |
|`SOBEL_Y             ` | Vertical edge detection.                            |![Image2](images/image_filter_sobel_y.png)           | ![Image2](images/image_filter_color_sobel_y.png)           |
|`EDGE_DETECT         ` | Edge detection all-directions                       |![Image3](images/image_filter_edge_detect.png)       | ![Image3](images/image_filter_color_edge_detect.png)       |
|`SMOOTHING           ` | Simple image smoothing.                             |![Image4](images/image_filter_smoothing.png)         | ![Image4](images/image_filter_color_smoothing.png)         |
|`SHARPEN_MODEST      ` | Simple image sharpen.                               |![Image5](images/image_filter_modest_sharp.png)      | ![Image5](images/image_filter_color_modest_sharp.png)      |
|`SHARPEN_AGGRESSIVE  ` | Sharpens image.                                     |![Image6](images/image_filter_aggressive_sharp.png)  | ![Image6](images/image_filter_color_aggressive_sharp.png)  |
|`GAUSSIAN_BLUR       ` | Approximated. See `GaussianBlur` for better kernel. |![Image7](images/image_filter_gaussian_blur.png)     | ![Image7](images/image_filter_color_gaussian_blur.png)     |
|`BLUR_HARD           ` | Image blur.                                         |![Image8](images/image_filter_hard_blur.png)         | ![Image8](images/image_filter_color_hard_blur.png)         |
|`BLUR_SOFT           ` | Image blur.                                         |![Image9](images/image_filter_soft_blur.png)         | ![Image9](images/image_filter_color_soft_blur.png)         |
|`HIGH_PASS           ` | High pass filter.                                   |![Image10](images/image_filter_high_pass.png)        | ![Image10](images/image_filter_color_high_pass.png)        |
|`EMBOSS              ` | Enhances edges.                                     |![Image11](images/image_filter_emboss.png)           | ![Image11](images/image_filter_color_emboss.png)           |
|`WEIGHTED_AVERAGE    ` | Filters with average.                               |![Image12](images/image_filter_weighted_average.png) | ![Image12](images/image_filter_color_weighted_average.png) |
|`DILATION_HORIZONTAL ` | "Smears" images horizontally.                       |![Image14](images/image_filter_dilation_x.png)       | |
|`DILATION_VERTICAL   ` | "Smears" image vertically.                          |![Image13](images/image_filter_dilation_y.png)       | |
|`DILATION            ` | "Smears" image in all directions.                   |![Image15](images/image_filter_dilation_xy.png)      | |