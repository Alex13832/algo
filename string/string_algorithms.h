//
// Created by Alexander Karlsson on 2019-10-13.
//

#ifndef ALGORITHM_SRC_STRING_STRING_H_
#define ALGORITHM_SRC_STRING_STRING_H_

#include <string>

class StringAlgorithm {

 public:
  static std::string BitapSearch(std::string text, std::string pattern);

  static std::vector<int> BoyerMore(std::string text, std::string pattern);

  static std::string LongestCommonSubstring(std::string A, std::string B);

 private:
  StringAlgorithm() { delete this; };

  static int LastOccurence(std::string str, char c);

};

#endif //ALGORITHM_SRC_STRING_STRING_H_
