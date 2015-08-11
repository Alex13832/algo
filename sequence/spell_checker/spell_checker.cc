/** ------------------------------------------------------------
* Implmentation of the SpellChecker class.
* Alexander Karlsson, begun 2015-08-07
* -------------------------------------------------------------- */
#include "spell_checker.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h> 
#include <cstdio>
#include <clocale>
using namespace std;

SpellChecker::SpellChecker(string ifile, string ofile, string lang) {
        setlocale(LC_ALL, "en_US.UTF-8");

        infile = ifile;
        outfile = ofile;

        string dict_file;

        if (lang == "eng") { 
                dict_file = "words_eng";
        
        } else if (lang == "swe") {
                dict_file = "words_swe";      
        
        } else if (lang == "esp") {
                dict_file = "words_esp";

        } else {
                cout << "Language not supported" << endl;
                exit(EXIT_FAILURE);
        }

        dict.init(dict_file);

}


/* Spell check-interface. Reads words from a file and checks if they
 are misspelled (not in the dictionary) and gives some suggestions. */
void SpellChecker::spellCheck() {
        list<string> words; 
        ifstream infil(infile);
        string line, temp;
        bool word_added = false;

        /* Get all text and split by whitespace */
        while (getline(infil, line)){
                string str(line);
                string buf; 		// buffer string
                stringstream ss(str);   // stream

                while (ss >> buf) words.push_back(buf);

                words.push_back("\n");

        }

        /* Out-file, TODO use args */
        ofstream file(outfile);

        /* Test all words */
        while (!words.empty()) {
                string word = words.front();
                words.pop_front();
                vector<char> spec_front;
                list<char> spec_back;

                if (word.length() > 2) {


                        while (!isalpha(word[0]) && (int)word[0] != -61) {
                                spec_front.push_back(word[0]);
                                word = word.substr(1,word.length());
                        }


                        while (!isalpha(word[word.length()-1]) && (int)word[word.length()-2] != -61) {
                                spec_back.push_front(word[word.length()-1]);
                                word = word.substr(0,word.length()-1);
                        } 

                }

                temp = word;
                temp[0] = tolower(temp[0]);

            	/* Don't care about them */
                if (word.size() < 3) {
                        bool linebreak = false;
                        if (word == "\n") linebreak = true;

                        standard_print(spec_front, spec_back, word, file, linebreak);

                }    	

                /* Check if the word exists in the dictionary */
                else if (dict.contains(word) || dict.contains(temp)) {
                            
                        standard_print(spec_front, spec_back, word, file, false);
            	
                } else {   
            		/* Get suggestions from dictionary */
                        vector<string> suggs = dict.get_suggestions(word);
                        
                        cout << endl;
                        cout << "Found misspelled word, " << "[";
                        cout << "\033[1;31m" << word << "\033[0;39m";
                        cout<< "]" << " suggestions:" << endl;
            		
                        /* Print the suggestions with a number */
                        size_t k = 1;
            		for (auto sugg: suggs) {
            			cout << "(" << k << ") " << sugg << " ";
                        k++; 
            		}

            		cout << "(" << k++ << ")" << " None " << "(" << k++ << ")" 
                        << " Other " << "(" << k++ << ")" << " Add the word"
                        << " (" << k++ << ") " << "Own and add" << endl;
            		
                        cout << "Enter your choice: ";
            		
                        size_t ki = 0;
            		while (ki <= 0 || ki > suggs.size()+4) cin >> ki;

            		if (ki <= suggs.size()) {
                                word = suggs[ki-1];

            		} else if (ki == suggs.size()+1) {
            			// Do nothing
            		
                        } else if (ki == suggs.size()+2) {
            			string own;
                                cout << "Enter your own: ";
            			cin >> own;
            			word = own;	
            		
                        } else if (ki == suggs.size()+3) {
                                dict.addWord(word);
                                word_added = true;
                        
                        } else if (ki == suggs.size()+4) {
                                string own; 
                                cout << "Enter word to add: ";
                                cin >> own;
                                word = own;
                                dict.addWord(word);
                                word_added = true;
                        }


                        standard_print(spec_front, spec_back, word, file, false);
            	
            	}
    		
    }

    if (word_added) dict.updateDictionary();

    file.close();
}


/* Simple print function, just to avoid reiteration of code */
void SpellChecker::standard_print(vector<char> spec_front, list<char> spec_back, 
        string word, ofstream& file, bool linebreak) {
        
        /* Put back special chars in front of word */
        if (!spec_front.empty()) {
                for (auto c: spec_front) {
                    cout << c;
                    file << c;
                }
        }

        /* Change color of word */
        cout << "\033[1;32m" << word << "\033[0;39m";
        file << word;

        /* Put back special chars at back of word */
        if (!spec_back.empty()) {
                for (auto c: spec_back) {
                        cout << c;
                        file << c;
                }
        }

        /* If there is a linebreak, don't use whitespace */
        if (!linebreak) {
                cout << " " << endl;
                file << " ";   
        }
}