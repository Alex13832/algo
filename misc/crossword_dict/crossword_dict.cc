/** ------------------------------------------------------------------
* This code produces a crossword dictionary of some input file with
* words. Any language will be accepted I guess.
* Alexander Karlson, begun 2015-08-15
* -------------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
using namespace std;


/* Makes the string word to lower case */
void to_lower(string& word) {
	transform(word.begin(),word.end(),word.begin(),[](char& ch){return tolower(ch);});
}

/* Produces a crossword dictionary of the words in infle and puts them in the
 file outfile */
void process_dictionary_file(string infile, string outfile) {
	ifstream file(infile);
	vector<string> words((istream_iterator<string>(file)),istream_iterator<string>());

	/* Reverse the word and sort a list, then reverse the word back
	 to get normal words. */
	transform(words.begin(),words.end(),words.begin(),[](string& word){
		to_lower(word);		
		reverse(word.begin(),word.end());
		return word;
	 });	

	sort(words.begin(),words.end());

	transform(words.begin(),words.end(),words.begin(),[](string& word){
		reverse(word.begin(),word.end());
		return word;
	});


	ofstream ofil;
	ofil.open(outfile);
	for_each(words.begin(),words.end(),[&](string& word){
		ofil << word << '\n';
	});	 
	ofil.close();
}

