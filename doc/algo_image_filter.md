Image filter algorithms
==============

## Image convolutions

```cpp
Img Convolve(const Img& im, KernelType filter_type)
```
Applies a convolution on the input image `im` with the kernel defined by the input `kernel_type`.

### Usage
```cpp
#using namespace algo::image;

... 
// Get images with some function or lib, convert to Img.
...

Img im_smooth_g{filter::Convolve(im_gray, filter::KernelType::SMOOTHING)};
Img3 im_smooth_c{filter::Convolvo{im_color, filter::KernelType::SMOOTHING}};
```

### Kernels and examples

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
|`DILATION_HORIZONTAL ` | "Smears" image horizontally. *                      |![Image14](images/image_filter_dilation_x.png)       | |
|`DILATION_VERTICAL   ` | "Smears" image vertically. *                        |![Image13](images/image_filter_dilation_y.png)       | |
|`DILATION            ` | "Smears" image in all directions. *                 |![Image15](images/image_filter_dilation_xy.png)      | |

(*) Takes an image convolved with `EDGE_DETECT` as input.

## Gaussian blur

```cpp
Img GaussianBlur(const Img& im, const Size& size, const float& sigma);
```
Will blur, also called smooth, the input image `im` by a Gaussian kernel defined by it's `size` and standard deviation `sigma`.
The larger size and standard deviation, the more smoothing will be added. It's also possible to run the function several times to apply more smoothing. 

[Gaussian blur, Wikipedia.](https://en.wikipedia.org/wiki/Gaussian_blur).

### Usage

```cpp
using namespace algo::image;

...

Img img1{GaussianBlur(im, Size{5, 5}, 1.0)};
// To get more smooting, use larger kernel size or/and standard deviation or run multiple times:
img1 = GaussianBlur(img1, Size{5, 5, 1.0});
img1 = GaussianBlur(img1, Size{5, 5, 1.0});
```

### Exampels

| Kernel size w x h | Standard deviation, sigma | Output |
|:---:|:---:|:---:|
| 5, 5      | 1.0 | ![Image](images/gauss_blur_5_5_1_0.png)     |
| 5, 5      | 1.5 | ![Image](images/gauss_blur_5_5_1_5.png)     |
| 11, 11    | 1.0 | ![Image](images/gauss_blur_11_11_1_0.png)   |
| 11, 11    | 1.5 | ![Image](images/gauss_blur_11_11_1_5.png)   |

## Median filter
```cpp
Img MedianFilter(const Img& im, const int& w_width, const int& w_height);

Img3 MedianFilter3(const Img3& im, const int& w_width, const int& w_height);
```
Should mainly be used to remove noise in the input image `im`. The window size defined by `w_width` and `w_height` will determine 
how large neighborhood the median will be based on. `MedianFilter` is for gray-scale images and `MedianFilter3` is for color images.

### Usage
```cpp
using namespace algo::image;

...

Img res{MedianFilter(im, 3, 3)};
```

### Examples

![Example noisy gs](images/lena_very_noisy.bmp) ![De-noised](images/median_lena_gray.png) ![Example noisy gs](images/lena_noisy_color.png) ![De-noised](images/median_lena_color.png)

## Binary thresholding
```cpp
Img Fixed(const Img& im, const uint8_t& threshold, const bool& cut_white);
```
Returns an image that has been thresholded at a fixed threshold value `threshold`. If `cut_white == true` the thresholding will 
set the values greater than the fixed threshold to white. If `cut_white == false` the pixel values are set to black instead.

### Usage
```cpp
using namespace algo::image;

...

Img im_thr{threshold::Fixed(im, 120, true)};
```

### Example

Order: Input, cut_white = true, cut_white = false

![Fixed threshold receipts.](images/image_fixed_thr.png)

## Adaptive thresholding
```cpp
Img Adaptive(const Img& im, const int& region_size, const bool& cut_white);
```
Instead of thresholding all pixes at the same fixed values, there's an option to threshold at a value fixed at the average
intensity value inside a sub-set of pixels, a rectangle with height = width = `region_size`.

### Usage
```cpp
using namespace algo::image;

...

Img im_thr{threshold::Adaptive(im, 12, true)};
```

### Example
![Adaptive threshold receipts.](images/image_adaptive_thr.png)

