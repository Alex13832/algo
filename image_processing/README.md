Image Processing algorithms
===================================================================
The aim for implementing this library is to implement functions for image processing from scratch.

[TOC]

### Algorithms
The following functions are implemented so far:

* Convolution
* Adaptive threholding

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
<img src="images/sudoku_adaptive15.png" height="270" alt="Screenshot"/>
</p>
