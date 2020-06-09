Image algorithms
================

This document will give an introduction to the image algorithms in this library. It will mainly cover the basic functions
and data structures required to work with the algotihms. 

## Namespaces
To access the various algorithms, a number of namepaces has been defined. The following table explains what they 
include.

| Namespace | Contains |
|---|---|
|`algo::image`| Basic data structures and and image processing tools.|
|`algo::image::feature`|Feature extraction algorihtms such as Hough transform and corner detection.|
|`algo::image::filter`|Filtering techniques such as convolution and Gaussian blur.|
|`algo::image::filter::threshold`| Binary and adaptive thresholding. |
|`algo::image::object`|Object detection algotihms such as Canny edges and line detection.|

## Data structures
Namespace `algo::image`

|Data structure| descrption| Example |
|:---|:---|:---|
|`Point`            |Cartesian coordinate.                          | `Point p{1, 2};`                                  | 
|`Line`             |Two-dimensional line.                          | `Line l{Point{1,2}, Point{2,3}};`                 |    
|`Size`             |Defines image size.                            | `Size s{5,5};`                                    |
|`Recangle`         |Used for accessing sub-images.                 | `Rectangle r{1,1,5,5};`                           |
|`Data8`            |Internal data structure in `Img`.              | `Data8 d{0,255,0,255};`                           |
|`Data32`           |Internal data structure in `IntegralImage`.    | `Data32 d{1,2,3,41131313};`                       |
|`Data8_3`          |Internal data structure in `Img3`, color.      | `Data8_3 d{{1,1,1,1}, {2,2,2,2}, {3,3,3,3}};`     |
|`Dataf`            |Internal data structure in `ImgF`.             | `Dataf d{0.5, 0.1, 0.2, 0.4};`|
|`Lines`            |Stores `Line` objects.                         |`Lines lines{Line{.},...,Line{.};`             |
|`Points`           |Stores `Point` objecs.                         |`Points pts{Point{1,2}, Point{3,4}};`|
|`Img3`             |Three channel, color image.                    ||
|`Img`              |The ordinary image data structure.             |`Img img{NewImgGray{5,5}};`|
|`ImgF`             |Image that uses floating point numbers.        ||
|`IntegralImage`    |For integral images.                           |`IntegralImage im{ImgToIntegralImage{img}};`|

## Standard functions

|Function|Description|
|:---|:---|
|`Img NewImgGray(const int& rows, const int& cols);`                        |Returns a new grayscale image with size defined by `rows` and `cols`.  |
|`Img ToGray(const Img3& img3);`                                            |Retuns a grayscale copy of `img3`.                                     |
|`Img InvertPixels(const Img& im);`                                         |For all intensities x in `im`: `x = 255 - x`.                          |
|`Img FlipX(const Img& im);`                                                |Mirrors image horizontally.                                            |
|`mg FlipY(const Img& im);`                                                 |Mirrors image vertically.                                              |
|`Img MaxOf(const Img& im1, const Img& im2);`                               |Take the maximum intensity values of `im1` and `im2`.                  |
|`IntegralImage ImgToIntegralImage(const Img& im);`                         |Computes and returns the [integral image](https://en.wikipedia.org/wiki/Summed-area_table) of `im`.                       |
|`uint32_t IntegralBoxSum(const IntegralImage& img, const Rectangle& box);` |Returns the pixel sum in the area `box` in `img`.  |