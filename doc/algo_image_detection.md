Image object detection alorithms
===================================


## Edge detection
To find edges in some input image, the Canny edge detection algorithm is used. Note that this is not a line detection
 algorithm, an edge is not always a (straight) line. There are simpler ways to find edges in the input image, the Sobel operator can find edges
  in the horizontal and vertical direction. The Canny edge detector normally detects high quality edges.
  
[Canny edge detector, Wikipedia.](https://en.wikipedia.org/wiki/Canny_edge_detector)
  
```cpp
Img object::ExtractCannyEdges(const Img& im, const int& threshold_min = 31, const int& threshold_max = 91);
```
Returns an image with the detected edges. `threshold_min`and `threshold_max` define the double threshold. In the
 Canny algorithm, a candidate edge pixel is set to strong when the pixel is over `threshold_max`, if the pixel is
  less than `threshold_max` but greater tha `threshold_min` then it's marked as weak. A weak edge is kept if it's in
   a neighborhood where some strong edge exists.
   
 ### Usage
```cpp
using namespace algo::image;

...

cons int kThreshMin{30};
const int kTreshMax{100};
// im must be a gray-scale image
Img im{object::ExtractCannyEdges(im, kThreshMin, kTreshMax)};
```

### Examples

Source code in `examples/image/detection/detect_canny_edges_example.cpp`.

![Canny edges](images/canny_sudoku.png)

![Canny highway](images/canny_highway.png)

## Line detection
The Hough transform is a central piece in the line detection algorithm. To learn how the algorithm determines where
 the lines are located in the input image go to the Wikipedia link below.
 
 [Hough transform, Wikipedia.](https://en.wikipedia.org/wiki/Hough_transform)
 
```cpp
Lines object::ExtractLines(const Img& im, const int& n, const int& min_line_dist, const int& min_line_sep = 10);
```
Returns a list of lines detected in the input image `im`, `n` is the maximum number of lines to return, note that the
 algorithm gives no guarantee that it find `n` lines. `min_line_dist` is the minimum lenght of a detected line and
  `min_line_sep` is a threshold to filter lines that are too close to each other.
  
### Usage
```cpp
#using namespace algo::image

...

//im_in is an input image.
Img im{object::ExtractCannyEdges(im_in, kThreshMin, kTreshMax)};
Lines lines{object::ExtractLines(im, kNbrLines, kMinLineDist, 10)};
```

### Examples
Source code in `examples/image/detect_hough_lines_example.cpp`.

![Lines in puzzle](images/lines_puzzle.png)

![Lines on road1](images/lines_road1.png)

![Lines on road2](images/lines_road2.png)


