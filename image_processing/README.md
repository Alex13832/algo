Image Processing algorithms
===================================================================
The aim for implementing this library is to implement functions for image processing from scratch.

[TOC]

### Algorithms
The following functions are implemented so far:

* Convolution
* Adaptive threholding
* Median filter
* Difference detector
* Template matching

### Convolution
Available filters (kernels):

* Sobel (x and y direction)
* Edge detection
* smoothing
* Sharpening
* Gaussian blur
* Embossing
* Weighted average
* Dilation (Requires binary images)

#### Test images

##### SOBEL-X, SOBEL-Y and EDGE_DETECT
<p align="center">
<img src="images/lena_sobel_x.png" height="270" alt="Screenshot"/>
<img src="images/lena_sobel_y.png" height="270" alt="Screenshot"/>
<img src="images/lena_edge_detect.png" height="270" alt="Screenshot"/>
</p>


##### SMOOTHING, SHARPEN_MODEST and SHARPEN_AGGRESSIVE
<p align="center">
<img src="images/lena_smoothing.png" height="270" alt="Screenshot"/>
<img src="images/lena_sharpen_modest.png" height="270" alt="Screenshot"/>
<img src="images/lena_sharepen_aggressive.png" height="270" alt="Screenshot"/>
</p>


##### GAUSSIAN_BLUR, BLUR_HARD and BLUR_SOFT
<p align="center">
<img src="images/lena_gaussian_blur.png" height="270" alt="Screenshot"/>
<img src="images/lena_blur_hard.png" height="270" alt="Screenshot"/>
<img src="images/lena_blur_soft.png" height="270" alt="Screenshot"/>
</p>


##### HIGH_PASS, EMBOSS and WEIGHTED_AVERAGE
<p align="center">
<img src="images/lena_high_pass.png" height="270" alt="Screenshot"/>
<img src="images/lena_emboss.png" height="270" alt="Screenshot"/>
<img src="images/lena_weighted_average.png" height="270" alt="Screenshot"/>
</p>

### Adaptive threshold
Outputs a thresholded image using an adaptive approach. Instead of using a fixed value to threshold on,
the pixels are thresholded on a mean value around the pixel.

<p align="center">
<img src="images/lena_adaptive15.png" height="270" alt="Screenshot"/>
</p>

### Median filter
This algorithm is using a median filter to remove noise in an image.
Compare in the example below before and after the median filter.

<p align="center">
<img src="input_images/lena_very_noisy.bmp" height="270" alt="Screenshot"/>
<img src="images/lena_median.png" height="270" alt="Screenshot"/>
</p>

### Difference detector
Detects the difference of an input reference image and a second image.
The image should have the same background. In the example below, I have used Lena
and Grumpy Lena as reference and comparison image respectively. In the third image
the result is shown.

#### LENA, GRUMPY_LENA and RESULT
<p align="center">
<img src="input_images/lena.png" height="270" alt="Screenshot"/>
<img src="input_images/grumpy_lena.png" height="270" alt="Screenshot"/>
<img src="images/lenas_diff.png" height="270" alt="Screenshot"/>
</p>

### Template matching
Finds a point where the intesity values meet in the reference image and the template image.
<p align="center">
<img src="input_images/template.png" height="50" alt="Screenshot"/>
<img src="input_images/lena.png" height="270" alt="Screenshot"/>
<img src="images/lena_template_match.png" height="270" alt="Screenshot"/>
</p>
