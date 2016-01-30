/** ---------------------------------------------------------------------------
* Finds the words in a "find the words" game
* Alexander Karlsson, begun 2016-01-29
*
* TODO print index
* Add custom dictionary
* --------------------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <string>

using namespace std;

struct Word {
	string str;
	int row, col; // x is column y is row
	int tag; // row = 0, rowR = 1, col = 2, colR = 3, diag = 4, diagR = 5, diagT = 6, diagTR = 7
	int found_tag;
	void print() {
		cout << row << " " << col << " " << str << " TAG: " << tag <<endl;
	}
};

// Reads a txt file, puts the rows and cols in vectors
void read_file(string file, vector<vector<char>>& mat)
{
	ifstream infile(file);
	string line;
	vector<string> rows;

      // Read lines, remove white spaces
	while (getline(infile, line)) {
		string str = line;
    		str.erase( remove_if( str.begin(), str.end(), ::isspace ), str.end() );
		rows.push_back(str);
	}

	// Create matrix
	vector<vector<char>> matrix(rows.size(),vector<char>(rows[0].length()));

	for (size_t i = 0; i < rows.size(); i++) {
		for (size_t j = 0; j < rows[0].length(); j++)
			matrix[i][j] = rows[i][j];
	}

	mat = matrix;
}

// Finds the diagonals of mat
vector<Word> diagonals(vector<vector<char>> mat)
{
	size_t h = mat.size(), w = mat[0].size();
	size_t col_count = 0, row_count = 0, sz = 0;
	vector<Word> words;

	while (col_count != w) {
		Word wrd; wrd.col= col_count; wrd.row = row_count; wrd.tag = 2;

		for (size_t j = 0; j < sz+1; j++)
			if (j + col_count < w)
				wrd.str += mat[row_count-j][j+col_count];

		words.push_back(wrd);

		if (row_count < h-1)
			row_count++, sz++;
		else
			col_count++;
	}
	return words;
}


// Reads a dictionary
vector<string> read_dictionary(string file)
{
      ifstream infile(file);
      string line;
      vector<string> rows;

      // Read lines, remove white spaces
      while (getline(infile, line)){
            string str = line;
            rows.push_back(str);
      }

      return rows;
}

// Compares with dictionary
vector<Word> find_words(vector<string> dict, vector<Word> candidates)
{
	vector<Word> wordsFound;

	// finds the substring (the words in dictionary) in candidates
	for (auto word: candidates) {
		for (auto dictWord: dict) {
			size_t pos = word.str.find(dictWord, 0);
			while (pos != string::npos)  {	// Found!
				if (dictWord.length() > 2) {
					Word tempW; // Save word
					cout << dictWord << endl;
					tempW.str = dictWord; tempW.row = word.row;
					tempW.col = word.col; tempW.tag = word.tag;
					tempW.found_tag = pos;
					wordsFound.push_back(tempW);
				}
				pos = word.str.find(dictWord,pos+1);
			}
		}
	}

	return wordsFound;
}

void process_game(string gameFile, string dictFile)
{
      vector<vector<char>> mat, matT;
      read_file(gameFile,mat);

	// Rows
	int count = 0;
	vector<Word> rows, rowsR;
	for (auto vec: mat) {
		string str(vec.begin(),vec.end());
		Word word; word.str = str; word.row = count; word.col = 0; word.tag = 0;
		rows.push_back(word);

		string strR(vec.rbegin(),vec.rend());
		Word wordR; wordR.str = strR; wordR.row = count++; wordR.col = 0; wordR.tag = 1;
		rowsR.push_back(wordR);
	}

	// Columns
	vector<Word> columns, columnsR;
	for (size_t i = 0; i < mat[0].size(); i++) {
		string str;
		for (size_t j = 0; j < mat.size(); j++) str += mat[j][i];

		Word word; word.str = str; word.row = 0; word.col = i; word.tag = 2;
		columns.push_back(word);

		string strR = str;
		reverse(strR.begin(), str.end());
		Word wordR; wordR.str = strR; wordR.row = 0; wordR.col = i; wordR.tag = 3;
		columnsR.push_back(wordR);
	}

	// Diagonals
	matT = mat;
	reverse(matT.begin(),matT.end());
	vector<Word> diag = diagonals(mat);
	vector<Word> diagT = diagonals(matT);
	vector<Word> diagR, diagTR;

	size_t height = mat.size() - 1;
	for (auto& w: diagT)
		w.row = height - w.row;


	// Reverse Diagonals
	for (auto& wrd: diag) {
		wrd.tag = 4;
		Word w = wrd;
		w.tag = 5;
		reverse(w.str.begin(),w.str.end());
		diagR.push_back(w);
	}
	for (auto& wrd: diagT) {
		wrd.tag = 6;
		Word w = wrd;
		w.tag = 7;
		reverse(w.str.begin(),w.str.end());
		diagTR.push_back(w);
	}



	vector<string> dict = read_dictionary(dictFile);

      //vector<Word> wordsFoundRows = find_words(dict, rows);
	vector<Word> wordsFoundRows = find_words(dict, rows);
	vector<Word> wordsFoundRowsR = find_words(dict, rowsR);
	vector<Word> wordsFoundCols = find_words(dict, columns);
	vector<Word> wordsFoundColsR = find_words(dict, columnsR);
	vector<Word> wordsFoundDiag = find_words(dict, diag);
	vector<Word> wordsFoundDiagR = find_words(dict, diagR);
	vector<Word> wordsFoundDiagT = find_words(dict, diagT);
	vector<Word> wordsFoundDiagTR = find_words(dict, diagTR);
}

int main() {
	// Will be modified with args, so custom list can be used
	string gameFile = "testfile.txt";
	string dictFile = "words_eng";

	process_game(gameFile, dictFile);
}
