/** -----------------------------------------------------------
* Finds the words in a "find the words" game
* Alexander Karlsson, begun 2016-01-29
*
* TODO print index
* Add custom dictionary
* ------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <string>

using namespace std;

// Reads a txt file, puts the rows and cols in vectors
void read_file(string file, vector<string>& rows, vector<string>& cols)
{
	ifstream infile(file);
	string line;

      // Read lines, remove white spaces
	while (getline(infile, line)){
		string str = line;
            str.erase( remove_if( str.begin(), str.end(), ::isspace ), str.end() );
            rows.push_back(str);
	}

      size_t lineLength = rows[0].length(), lines = rows.size();

      // Read columns
      for (size_t i = 0; i < lineLength; i++) {
            string colStr;
            for (size_t j = 0; j < rows.size(); j++)
                  colStr += rows[j][i];

            cols.push_back(colStr);
      }
}

// Generates all diagonal strings
vector<string> diagonals(vector<string> rows)
{
      size_t lineLength = rows[0].length(), lines = rows.size();
      string matrix;

      // Add all rows as a string "matrix"
      for (auto str: rows) matrix += str;

      size_t max_diag_length = min(lineLength,lines), current_length = 1;
      int jump_length = lineLength - 2;

      vector<string> diag;
      vector<int> pivots;
      vector<bool> visited(100,false);

      stringstream ss;
      string s;
      ss << matrix[0];
      ss >> s;
      diag.push_back(s);

      // Calculate where every new diag-string starts
      for (size_t i = 0; i < matrix.length(); i += lineLength)
            pivots.push_back(i);

      // Add the final diag-strings located at the back
      if (pivots.back()+1 < matrix.length()) {
            for (size_t j = pivots.back()+1; j < matrix.length(); j++)
                  pivots.push_back(j);
      }

      // generate the diagonals usging the pivots
      for (auto pivot: pivots) {
            int jumps = 0;
            string str;
            stringstream ss2;

            for (int k = pivot; k > 0; k-=jump_length+1) {
                  if (visited[k] == false) ss2 << matrix[k];

                  visited[k] = true;
            }

            ss2 >> str;
            diag.push_back(str);
      }

      diag.erase(diag.begin()+1,diag.begin()+2);

      return diag;
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
void find_words(vector<string> dict, vector<string> candidates)
{
      for (auto word: candidates) {
            // Check if word contains dictionary words (slow?)
            for (auto dict_word: dict) {

                  // Word length of 2 gives a lot of crap
                  if (word.find(dict_word) != std::string::npos && dict_word.length() > 2) {
                        cout << dict_word << endl;
                  }
            }
      }
}

int main()
{

      string file = "testfile.txt";
      vector<string> rows,cols;
      read_file(file,rows,cols);

      vector<string> diag = diagonals(rows);

      vector<string> colsR = cols;

      reverse(colsR.begin(),colsR.end());
      vector<string> diagR = diagonals(colsR);
      reverse(colsR.begin(),colsR.end());

      vector<string> dict = read_dictionary("words_eng");

      find_words(dict,rows);
      find_words(dict,cols);
      find_words(dict,diag);
      find_words(dict,diagR);
}
