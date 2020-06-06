Feture extraction algorithms
==========================

## Hough transform
The Hough transform is mainly used in line detection. At least in this library. This function enables line detection
 but is of course free to use for other purposes. Note that this is not a generalized Hough transform, which means
  that the purpose is line detection.
  
[Hough transform, Wikipedia.](https://en.wikipedia.org/wiki/Hough_transform)

```cpp
Img feature::HoughTransform(const Img& im);
```
Returs the Hough transform as a new image. The image can now be used to search for local maximums (lines).

## Usage
```cpp
using namespace algo::image;

...

// im is a gray-scale image
Img imh{feature::HoughTransform(im)};
```

### Examples

![Puzzle](images/hough_transform_puzzle.png)

![Puzzle](images/hough_transform_road.png)

## Corner detection
A traditional corner detector uses some way to measure how much a pixel is a corner. This library offers the Harris- and
 Shi-Tomasi- cornerness calculations.
 
[Corner detectors, WIkipedia.](https://en.wikipedia.org/wiki/Corner_detection)
 
[Lecture notes, Saad J Bedros, University of Minnesota.](https://bit.ly/2XzCuis)
 
```cpp
Points feature::Corners(const Img& im, const int& threshold, const CornerDetType& det_type = CornerDetType::kHarris,
                       const int& n_best = 0, const int& min_dist = 0,
                       const GaussWindowSettings& g_win_set = {Size{7, 7}, 1.0});
```
Returns a list of coordinates of corners in the input image `im`. By default, the `CornerDetType:kHarris
` (`CornerDetType::kShiTomasi`) is
 selected
. The user chan select to get the `n_best`, the n corners with the highest measure of corner. It's also possible to
 select the minimum distance between two pair of points, `min_dist`. To vary the quality of found corners, it's
  recommended to tweak the Gaussian kernel window size and standard deviation in `g_win_set`. Note that the window
   dimensions must be odd integers.
   
 The computation speed is dependent on the image size and the other input parameters.
   
 ### Usage
 ```cpp
using namespace algo:image;

... 

Points points{feature::Corners(im, 9e2, feature::CornerDetType::kShiTomasi, 0, 4, {5, 5, 1.0})};
 ```

### Examples

![Coners in puzzle.](images/corners_puzzle.png) 

![Coners in building, picture from Wikipedia.](images/corners_building.png) 
