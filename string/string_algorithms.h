//
// Created by Alexander Karlsson on 2019-10-13.
//

#ifndef ALGORITHM_SRC_STRING_STRING_H_
#define ALGORITHM_SRC_STRING_STRING_H_

#include <string>

class StringAlgorithm {

 public:
  static std::string bitap_search(std::string text, std::string pattern);

  static std::vector<int> boyer_moore(std::string text, std::string pattern);

 private:
  StringAlgorithm() { delete this; };

  static int last_occurence(std::string str, char c);

};

#endif //ALGORITHM_SRC_STRING_STRING_H_
