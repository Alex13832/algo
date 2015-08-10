/** ------------------------------------------------------------
* Dictionary class, contains contains algorithms and functions
* for determining suggestions for replacing misspelled words.
* Alexander Karlsson, begun 2015-08-07
* -------------------------------------------------------------- */
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include <map>
#include "word.h"

#define max_word_size 25
#define d_size 26

class Dictionary {
public:
    Dictionary();
    void init(std::string lang);
    bool contains(std::string word);
    std::vector<std::string> get_suggestions(std::string word);
    void addWord(const std::string newWord);
    void updateDictionary();

private:
    void preProcess();
    bool file_exists(std::string filename);
    void readLinesInFile(std::string filename, std::vector<std::string>& wrds);
    void readWordFile();
    std::vector<std::string> getTrigrams(std::string word);
    void add_trigram_suggestions(std::vector<std::string>& suggestions, const std::string& word);
    void rank_suggestions(std::vector<std::string>& suggestions, std::string word);
    void trim_suggestions(std::vector<std::string>& suggestions);
    std::vector<Word> words[max_word_size];
    std::map<std::string,bool> words_content;
    std::string dict_file, file, file_out;
};

#endif // DICTIONARY_H
