[![Build Status](https://travis-ci.org/alex011235/algo.svg?branch=master)](https://travis-ci.org/alex011235/algo) [![codecov](https://codecov.io/gh/alex011235/algo/branch/master/graph/badge.svg)](https://codecov.io/gh/alex011235/algo)

Algo :rocket:
===============================
This repository contains C++ implementations of various known algorithms from selected fields of algorithm design

* [Bit manipulation](https://github.com/alex011235/algo/blob/master/doc/algo_bit.md)
* [Data mining](https://github.com/alex011235/algo/blob/master/doc/algo_data_mining.md)
* [Computational geometry](https://github.com/alex011235/algo/blob/master/doc/algo_geometry.md)
* [Graph theory](https://github.com/alex011235/algo/blob/master/doc/algo_graph.md)
* [Greedy algorithms](https://github.com/alex011235/algo/blob/master/doc/algo_greedy.md)
* Image analysis and computer vision
    * [Feature detection](https://github.com/alex011235/algo/blob/master/doc/algo_image_feature.md)
    * [Filters](https://github.com/alex011235/algo/blob/master/doc/algo_image_filter.md)
    * [Object detection](https://github.com/alex011235/algo/blob/master/doc/algo_image_object.md)
* [Network algorithms](https://github.com/alex011235/algo/blob/master/doc/algo_network.md)
* [Puzzle solving](https://github.com/alex011235/algo/blob/master/doc/algo_puzzle.md)
* [Searching](https://github.com/alex011235/algo/blob/master/doc/algo_search.md)
* [Sequence](https://github.com/alex011235/algo/blob/master/doc/algo_sequence.md)
* [Sorting](https://github.com/alex011235/algo/blob/master/doc/algo_sort.md)
* [Strings](https://github.com/alex011235/algo/blob/master/doc/algo_string.md)
* [Transforms](https://github.com/alex011235/algo/blob/master/doc/algo_transform.md)

## Build
If an IDE is used, it has to be able to handle CMake files. An excellent IDE for C++ is [CLion](https://www.jetbrains.com/clion/), 
which unfortunately is not free (€19.90 monthly).

Run the following commands inside the root directory of this project:
```shell script
mkdir build
cd build
cmake ..
make
```

To run the unit tests, execute after the `make` command above
```shell script
ctest .
```

The result should look like:
```shell script
❯ ctest .
Test project /Users/alex011235/code/algo/build
    Start 1: AlgoTests
1/1 Test #1: AlgoTests ........................   Passed    4.09 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   4.10 sec
```
Note that this is a collection of (>200) test cases. If you wish to execute each test case one by
one, navigate to `<algo-root>/build/test` and execute

```shell script
./algo_tests
```
and expect:
```shell script
❯ ./algo_tests
Running main() from /Users/alex011235/code/algo/test/gtest/googletest/src/gtest_main.cc
[==========] Running 214 tests from 14 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from test_algo_puzzle
[ RUN      ] test_algo_puzzle.soduku_difficult
[       OK ] test_algo_puzzle.soduku_difficult (1087 ms)
[ RUN      ] test_algo_puzzle.sudoku_extreme
[       OK ] test_algo_puzzle.sudoku_extreme (28 ms)
[ RUN      ] test_algo_puzzle.sudoky_invalid_row
[       OK ] test_algo_puzzle.sudoky_invalid_row (382 ms)
[ RUN      ] test_algo_puzzle.sudoku_invalid_column
[       OK ] test_algo_puzzle.sudoku_invalid_column (3 ms)
[ RUN      ] test_algo_puzzle.sudokU_invalid_cell
[       OK ] test_algo_puzzle.sudokU_invalid_cell (1 ms)
[----------] 5 tests from test_algo_puzzle (1501 ms total)

[----------] 25 tests from test_algo_image
[ RUN      ] test_algo_image.test_canny_edge
[       OK ] test_algo_image.test_canny_edge (4 ms)
[ RUN      ] test_algo_image.test_line_detection
[       OK ] test_algo_image.test_line_detection (175 ms)
...
```

## Constraints

The algorithms are implemented **only** using the C++ standard library.

The examples in `examples/` may use additional libraries but should not be required when building the library itself.

## Resources

### Documentation :paperclip:

See the `doc` folder for documentation. The plots in the documentation has been generated with python and [Plotly](https://plotly.com).

### Data
Most of the test data has been generated thanks to the [Orange](https://orange.biolab.si) data mining tool.

### Examples

See the `examples` directory for examples. To run some of the examples, [OpenCv](https://opencv.org) is required.

To run the examples, simply provide and set the cmake flag `COMPILE_EXAMPLES`. If you wish to build the image
algorithm examples the you must provide and set the flag `OPENCV_INSTALLED`, if this flag is not set, the 
remaining examples will be built and compiled. Full example to build all examples:
```shell script
mkdir build
cd build
cmake .. -DCOMPILE_EXAMPLES=1 -DOPENCV_INSTALLED=1
make
```
and navigate to the examples directory and find an example to run.

### Unit tests :white_check_mark:
The C++ code is tested with the [Google Test](https://github.com/google/googletest) framework. 

## Donate 

Paypal

![Paypal](doc/images/QR-kod.png)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=st.alexander85%40gmail.com&item_name=A+small+donation+to+a+happy+coder&currency_code=USD&source=url)
