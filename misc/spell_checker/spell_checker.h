/** ------------------------------------------------------------
* Spell-checher interface. Reads files and runs the words
* through the functions and algorithms in dictionary.
* Alexander Karlsson, begun 2015-08-07
* -------------------------------------------------------------- */
#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <iostream>
#include <string>
#include "dictionary.cc"
#include <vector>
#include <list>
#include <fstream>

class SpellChecker {

 public:
  SpellChecker(std::string ifile, std::string ofile, std::string lang);
  void spellCheck();

 private:
  void standard_print(std::vector<char> spec_front, std::list<char> spec_back,
                      std::string word, ofstream &file, bool linebreak);

  std::string infile, outfile, language;
  Dictionary dict;
};

#endif