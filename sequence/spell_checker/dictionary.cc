/** ------------------------------------------------------------
* Implementation of class Dictionary
* Alexander Karlsson, begun 2015-08-07
* -------------------------------------------------------------- */
#include "dictionary.h"
#include "word.cc"
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <sstream>
#include <cmath>
using namespace std;

/* Constructor. The dictionary file must be processed if the 
 file with trigrams does not exist. */
Dictionary::Dictionary() { }


void Dictionary::init(string lang) {
    dict_file = lang;
    file = "lang_files/" + dict_file;
    file_out = "lang_files/" + dict_file + "_out.txt";
    
    if (!file_exists(file_out)) preProcess();
    
    readWordFile();
}


/* Routine for reading dictionary, storing tri-grams etc. */
void Dictionary::preProcess() {
    vector<string> wrds;

    readLinesInFile(file, wrds);

    vector<string> trigs;
    ofstream file(file_out);

    for (auto w: wrds) {
        trigs = getTrigrams(w);
        int trigs_count = trigs.size();

        file << w << " " << trigs_count << " ";
        for (auto tr: trigs) file << tr << " ";
        file << '\n';
    }
    file.close();
}


/* Reads the file with word and trigrams */
void Dictionary::readWordFile() {
    ifstream infile(file_out);
    string line;

    while (getline(infile, line)){
        string str(line);
        string buf; // buffer string
        stringstream ss(str); // stream
        vector<string> splitted;

        while (ss >> buf) splitted.push_back(buf);
        vector<string> trigs;
     
        string wrd = splitted[0];

        words_content[wrd] = true;

        for (auto it = splitted.begin()+2; it!=splitted.end(); ++it) {
            trigs.push_back(*it);
        }

        Word W(wrd, trigs);
        words[wrd.size()].push_back(W);

        
    }
}


/* Returns spelling suggestions for the misspelled word */
vector<string> Dictionary::get_suggestions(string word) {
    vector<string> suggestions;
    add_trigram_suggestions(suggestions, word);
    rank_suggestions(suggestions, word);
    trim_suggestions(suggestions);
    return suggestions;
}


/* Checks if word exists in the dictionary */
bool Dictionary::contains(string word) {
    return (words_content[word]);
}


/* Check if filname exists*/
bool Dictionary::file_exists(string filename) {
    ifstream infile(filename);
    return infile.good();
}


/* Read all the lines in the disk-dictionary,
 store them in words as lower case words */
void Dictionary::readLinesInFile(string filename, vector<string>& wrds) {
    ifstream infile(filename);
    string line;

    while (getline(infile, line)) {
        string temp;
        //for (size_t i = 0; i < line.length(); ++i) temp+=tolower(line[i]);
        for (size_t i = 0; i < line.length(); ++i) temp+=(line[i]);
        wrds.push_back(temp);
    }
}


/* Returns the sorted trigrams for word */
vector<string> Dictionary::getTrigrams(string word) {
    vector<string> trigrams;
    string tri;

    if (word.length() < 3) {
        trigrams.push_back(word);
        return trigrams;
    }

    for (size_t i = 0; i < word.length()-2; ++i) {
        tri = word.substr(i,3);
        trigrams.push_back(tri);
    }

    sort(trigrams.begin(),trigrams.end());

    return trigrams;
}


/* Add words to suggestions with the size +-1 letters and that have at least
 *  half the size of the trigrams in common with word */
void Dictionary::add_trigram_suggestions(vector<string>& suggestions, const string& word) {
    int len = word.length();
    vector<string> word_trigs = getTrigrams(word);
    size_t word_trigs_size = word_trigs.size();

    for (int i = len-1; i <= len+1; i++) {
        vector<Word> W = words[i];
        for (auto wrd: W) {

            if (wrd.get_matches(word_trigs) >= (word_trigs_size/2))
                suggestions.push_back(wrd.get_word());
        }
    }
}


/* A word candidate */
struct Candidate {
    string cand;
    int cost = 0;
};


/* To be used when sorting the candidates according to their
 edit distances */
struct candidate_comp {
  bool operator() (const Candidate c1, const Candidate c2) const
  {return c1.cost < c2.cost;}
};


/* Returns the cost of changing word_a to word_b according 
 to the Levenshtein distance, the smaller the better. */
int distance(string word_a, string word_b) {
    size_t a_size = word_a.length();
    size_t b_size = word_b.length();
    int d[d_size][d_size];

    for (size_t i = 1; i <= a_size; i++) d[i][0] = 1;
    for (size_t i = 1; i <= b_size; i++) d[0][i] = 1;

    for (size_t i = 1; i <= a_size; i++) {
        for (size_t j = 1; j <= b_size; j++) {
            int a,b,c;
            word_a[i-1] == word_b[j-1] ? a = d[i-1][j-1] : a = d[i-1][j-1]+1;
            b = d[i-1][j]+1;
            c = d[i][j-1]+1;
            d[i][j] = min(a,min(b,c));
        }
    }

    return d[a_size][b_size];
}


/* Ranks the suggestions after their edit distance */
void Dictionary::rank_suggestions(vector<string> &suggestions, string word) {
    vector<Candidate> candidates;
   
    for (auto sugg: suggestions) {
        Candidate c;
        c.cand = sugg;
        candidates.push_back(c);
    }

    for (auto& candi: candidates) {

        /* The actual edit distance here */
        candi.cost = distance(word,candi.cand);
    }

    sort(candidates.begin(),candidates.end(),candidate_comp());
    suggestions.clear();

    for (auto candidate: candidates) {
        suggestions.push_back(candidate.cand);
    }
}


/* Trims the suggestions, removes all but the five first, iff
 there are at least five. */
void Dictionary::trim_suggestions(vector<string> &suggestions) {
    if (suggestions.size() > 4) {
        suggestions.erase(suggestions.begin()+5,suggestions.end());
    }
}


/* Adds a new word to the dictionary, both in the ordinary 
 dictionary file and in the "trigrams-dictionary" file. */
void Dictionary::addWord(string newWord) {
    //TODO: implement
    //All words must be sorted.
    if (!words_content[newWord]) {
        words_content[newWord] = true;
        
        vector<string> trigs = getTrigrams(newWord);
        size_t amnt = trigs.size();
        Word W(newWord, trigs);

        words[newWord.length()].push_back(W);

        sort(words[newWord.length()].begin(), words[newWord.length()].end(), word_comp());

    }
}


/* Updates the dictionary, adds new words to the files stored on disk.
 Is only to be run at program termination. */
void Dictionary::updateDictionary() {
    ofstream file1(file_out), file2(file);
    vector<string> all_words;

    for (auto word_sub: words) {
        for (auto word: word_sub) {
            vector<string> trigs = word.get_trigrams();
            int s = trigs.size();
            string w = word.get_word();

            all_words.push_back(w);

            file1 << w << " " << s << " ";
            for (auto tr: trigs) file1 << tr << " ";
            file1 << '\n';

        }

    }

    file1.close();

    sort(all_words.begin(), all_words.end());

    for (auto w: all_words) {
        file2 << w << "\n";
    }

    file2.close();
}
