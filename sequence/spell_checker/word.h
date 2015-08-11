/** ------------------------------------------------------------
* Class for Word, contains a string word ad its trigrams.
* Alexander Karlsson, begun 2015-08-07
* -------------------------------------------------------------- */
#ifndef WORD_H
#define WORD_H

#include <vector>
#include <string>

class Word {
public:
    Word(const std::string& w, const std::vector<std::string>& t);
    std::string get_word() const;
    unsigned int get_matches(const std::vector<std::string>& t);
    std::vector<std::string> get_trigrams() { return trigrams; }

private:
    std::string word;
    std::vector<std::string> trigrams;



};

#endif // WORD_H
