/** ---------------------------------------------------------------------------
* Finds the words in a "find the words" game
* Alexander Karlsson, begun 2016-01-29
*
* Add custom dictionary
* --------------------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int height, width;

enum Mode {isRow, isCol, isDiag, isDiagT};

struct Word {
	string str;
	int rowStart, colStart, rowEnd, colEnd;
};

// Reads a txt file, puts the rows and cols in vectors
vector<vector<char>> read_file(string file)
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

	return matrix;
}

// Reads a dictionary
vector<string> read_dictionary(string file)
{
      ifstream infile(file);
      string line;
      vector<string> rows;

      // Read lines
      while (getline(infile, line))
            rows.push_back(line);

      return rows;
}

// Finds the diagonals of mat
vector<string> diagonals(vector<vector<char>> mat)
{
	size_t h = mat.size(), w = mat[0].size();
	size_t col_count = 0, row_count = 0, sz = 0;
	vector<string> words;

	while (col_count != w) {
		string str;

		for (size_t j = 0; j < sz+1; j++)
			if (j + col_count < w)
				str += mat[row_count-j][j+col_count];

		words.push_back(str);

		if (row_count < h-1)
			row_count++, sz++;
		else
			col_count++;
	}
	return words;
}

// Compares with dictionary
vector<Word> find_words(vector<string> dict, vector<string> candidates, Mode mode)
{
	vector<Word> wordsFound;
	int count = 0;

	// finds the substring (the words in dictionary) in candidates
	for (auto word: candidates) {
		string wordRev = word;
		reverse(wordRev.begin(), wordRev.end());

		for (auto dictWord: dict) {
			size_t pos = word.find(dictWord, 0); // forward use
			size_t posR = wordRev.find(dictWord, 0); // reverse

			while (pos != string::npos)  {	// Found!
				if (dictWord.length() > 2) {
					Word w; w.str = dictWord;
					if (mode == isRow) {
						w.rowStart = count; w.colStart = pos;
						w.rowEnd = count; w.colEnd = pos + dictWord.length()-1;

					} else if (mode == isCol) {
						w.rowStart = pos; w.colStart = count;
						w.rowEnd = pos + dictWord.length()-1; w.colEnd = count;

					} else if (mode == isDiag) {
						if (count >= height) {
							w.rowStart = height - pos - 1;
							w.colStart = count - height + pos + 1;
						} else {
							w.rowStart = count - pos;
							w.colStart = pos;
						}
						w.rowEnd = w.rowStart - dictWord.length() + 1;
						w.colEnd = w.colStart + dictWord.length() - 1;

					} else if (mode == isDiagT) {
						if (count >= height) {
							w.rowStart = pos;
							w.colStart = count - height + pos + 1;
						} else {
							w.rowStart = height - count + pos - 1;
							w.colStart = pos;
						}
						w.rowEnd = w.rowStart + dictWord.length() - 1;
						w.colEnd = w.colStart + dictWord.length() - 1;
					}

					wordsFound.push_back(w);
				}
				// update
				pos = word.find(dictWord,pos+1);
			}

			while (posR != string::npos)  {	// Found!
				if (dictWord.length() > 2) {
					Word w; w.str = dictWord;

					if (mode == isRow) {
						w.rowStart = count; w.colStart = width - posR-1;
						w.rowEnd = count; w.colEnd = width-posR-dictWord.length();

					} else if (mode == isCol) {
						w.rowStart = height-posR-1; w.colStart = count;
						w.rowEnd = height-posR-dictWord.length(); w.colEnd = count;

					} else if (mode == isDiag) {
						if (count >= height) {
							w.rowStart = count - height + posR - 1;
							w.colStart = count - height + word.length() - posR;
						} else {
							w.rowStart = posR;
							w.colStart = word.length() - posR - 1;
						}
						w.rowEnd = w.rowStart + dictWord.length()-1;
						w.colEnd = w.colStart - dictWord.length()+1;

					} else if (mode == isDiagT) {
						if (count >= height) {
							w.rowStart = word.length() - posR - 1;
							w.colStart = count - height + w.rowStart + 1;
						} else {
							w.rowStart = height - posR - 1;
							w.colStart = count - posR;
						}
						w.rowEnd = w.rowStart - dictWord.length() + 1;
						w.colEnd = w.colStart - dictWord.length() + 1;
					}

					wordsFound.push_back(w);
				}
				posR = wordRev.find(dictWord,posR+1);
			}
		}
		count++;
	}

	return wordsFound;
}

vector<Word> process_game(vector<vector<char>> mat, vector<string> dict)
{
      vector<vector<char>> matT;

	// Rows
	vector<string> rows;
	for (auto vec: mat) {
		string str(vec.begin(),vec.end());
		rows.push_back(str);
	}

	// Columns
	vector<string> columns;
	for (size_t i = 0; i < mat[0].size(); i++) {
		string str;
		for (size_t j = 0; j < mat.size(); j++) str += mat[j][i];
		columns.push_back(str);
	}

	// Diagonals
	matT = mat;
	reverse(matT.begin(), matT.end());

	vector<string> diag = diagonals(mat);
	vector<string> diagT = diagonals(matT);

	vector<Word> wrows = find_words(dict, rows, Mode(isRow));
	vector<Word> wcols = find_words(dict, columns, Mode(isCol));
	vector<Word> wdiag = find_words(dict, diag, Mode(isDiag));
	vector<Word> wdiagt = find_words(dict, diagT, Mode(isDiagT));

	vector<Word> result;
	result.insert(result.end(), wrows.begin(), wrows.end());
	result.insert(result.end(), wcols.begin(), wcols.end());
	result.insert(result.end(), wdiag.begin(), wdiag.end());
	result.insert(result.end(), wdiagt.begin(), wdiagt.end());

	return result;

}

int main(int argc, const char *argv[]) {
	// Will be modified with args, so custom list can be used
	string gameFile; // = "testfile.txt";
	string dictFile; // = "words_eng";
	string resFile;
	if (argc > 3) {
		gameFile = argv[1];
		dictFile = argv[2];
		resFile = argv[3];
	} else {
		cout << "wrong input format" << endl;
		exit(0);
	}

	vector<vector<char>> mat = read_file(gameFile);
	width = mat[0].size(); height = mat.size();
	cout << width << " " << height << endl;
	vector<string> dictionary = read_dictionary(dictFile);

	vector<Word> res = process_game(mat, dictionary);

	ofstream outfile;
	outfile.open(resFile);

	for (auto w: res) {
		outfile << "at " << w.rowStart << " " << w.colStart << " to " <<
		w.rowEnd << " " << w.colEnd << " " << w.str << endl;
	}
	outfile.close();

	return 0;
}
