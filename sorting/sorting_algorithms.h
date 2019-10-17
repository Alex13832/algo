//
// Created by Alexander Karlsson on 2019-10-16.
//

#ifndef ALGORITHM_SORTING_SORTING_H_
#define ALGORITHM_SORTING_SORTING_H_

#include <vector>
#include <iostream>
#include <list>

class Sorting {

 private:

 public:
  Sorting() {};

  static std::vector<int> BubbleSort(std::vector<int> lst);

  static std::vector<int> MergeSort(std::vector<int> &lst);

};

#endif //ALGORITHM_SORTING_SORTING_H_
