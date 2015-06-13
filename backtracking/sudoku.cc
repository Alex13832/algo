/**
* A backtracking algorithm for solving a sudoku game.
* File input as arg: files/<file>.txt
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <string>
using namespace std;

 /* Checks if a row is valid*/
bool row_valid(vector<vector<int>> grid, int row, int num) {
	for (size_t i = 0; i < 9; ++i) {
		if (grid[row][i] == num) return false;
	}
	return true;
}

/* Checks if a column is valid */
bool col_valid(vector<vector<int>> grid, int col, int num) {
	for (size_t i = 0; i < 9; ++i) {
		if (grid[i][col] == num) return false;
	}
	return true;
}

/* Checks if a 3x3 cell is valid */
bool cell_valid(vector<vector<int>> grid, int row, int col, int num) {
	int r1 = row - row%3;
	int r2 = r1 + 3;
	int c1 = col - col%3;
	int c2 = c1+3;

	for (int i = r1; i < r2; ++i) {
		for (int j = c1; j < c2; ++j) {
			if (grid[i][j] == num) return false;
		}
	}
	return true;
}



bool sudoku(vector<vector<int>>& grid, int x, int y) {
	while (x < 9 && grid[x][y] != 0) {
		y++;
		if (y == 9) {
			x++;
			y = 0;
		}
	}
	if (x == 9) return true;


	for (size_t i = 1; i < 10; i++) {
		if (row_valid(grid,x,i) && col_valid(grid,y,i) && cell_valid(grid,x,y,i)) {
			grid[x][y] = i;
			if (sudoku(grid,x,y)) return true;
		}
	}
	
	grid[x][y] = 0;
	return false;
}


void read_grid(vector<vector<int>> & grid, string file){
	ifstream infile(file);
	string line;
	int row = 0;
	int col = 0;
	while (getline(infile, line)){	
		string s = line;
		string delimiter = " ";

		size_t pos = 0;
		string token;
		while ((pos = s.find(delimiter)) != string::npos) {
		    	token = s.substr(0, pos);
			try {
				
				int num = stoi(token);
				grid[row][col] = num;

			} catch (std::invalid_argument&) { }

		    	s.erase(0, pos + delimiter.length());
			col++;
		}

		try {
			int num = stoi(s);
			grid[row][col] = num;
		} catch (std::invalid_argument&) { }
 		
		row++;
		col = 0;
	}
	
	cout << "-----------------------------------------" << endl; 
	cout << file << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------------" << endl;
	

}

int main(int argc, const char *argv[]) {
	clock_t t0, t1;
	string file;
	if (argc > 0) {
		file = argv[1];
	} else {
		file = "files/difficult.txt";
	}

	vector<vector<int>> grid(9,vector<int>(9,0));
	read_grid(grid,file);
	
	t0 = clock(); // Only algorithm time
	sudoku(grid,0,0);
	t1 = clock();

	cout << "SOLUTION" << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);
}
