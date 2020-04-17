/** ------------------------------------------------------------
* Implementation of Word, contains a string word ad its trigrams.
* Alexander Karlsson, begun 2015-08-07
* -------------------------------------------------------------- */
#include "word.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* To be used when sorting Words */
struct word_comp {
  bool operator()(const Word w1, const Word w2) const
  { return w1.get_word() < w2.get_word(); }
};

Word::Word(const string &w, const vector<string> &t) : word(w), trigrams(t)
{}

/* Returns the std string word */
string Word::get_word() const
{
  return word;
}

/* Returns how many of the trigrams that match with the trigrams in t */
unsigned int Word::get_matches(const vector<string> &t)
{
  uint count = 0;

  for (auto tri: t) {
    if (find(trigrams.begin(), trigrams.end(), tri) != trigrams.end()) count++;
  }

  return count;
}
