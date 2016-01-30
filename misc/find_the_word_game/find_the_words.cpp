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
	int tag; // 0 row 1 col 2 diag 3 diagR

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
void find_words(vector<Word> diag, vector<Word> diagR)
{

	for (auto w: diag)
		cout << w.row << " " << w.col << " " << w.str << endl;

	cout << endl;

	for (auto w: diagR)
		cout << w.row << " " << w.col << " " << w.str << endl;

}

int main()
{
      string file = "testfile.txt";
      vector<vector<char>> mat, matT;
      read_file(file,mat);

	matT = mat;
	reverse(matT.begin(),matT.end());

	vector<Word> diag = diagonals(mat);
	vector<Word> diagR = diagonals(matT);

	size_t height = mat.size() - 1;
	for (auto& w: diagR)
		w.row = height - w.row;




	vector<string> dict = read_dictionary("words_eng");

      find_words(diag, diagR);
}
