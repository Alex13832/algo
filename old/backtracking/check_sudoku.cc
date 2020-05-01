/** ----------------------------------------------------------------------------
 Validates whether a sudoku (with all entries filled) is a valid solution or not.
 Alexander Karlsson 2016-10-16
----------------------------------------------------------------------------- */
#include <iostream>

#define N 9

using namespace std;

/* Checks if a row is valid */
bool row_valid(int grid[N][N], int row)
{
    int thiz_row [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (size_t i = 0; i < 9; ++i)
       thiz_row[grid[row][i]]++;

    for (int i = 1; i < 10; i++)
        if (thiz_row[i] == 0 || thiz_row[i] > 1)
            return false;

   return true;
}

/* Checks if a column is valid */
bool col_valid(int grid[N][N], int col)
{
    int thiz_col [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (size_t i = 0; i < 9; ++i)
       thiz_col[grid[i][col]]++;

    for (int i = 1; i < 10; i++)
        if (thiz_col[i] == 0 || thiz_col[i] > 1)
            return false;

   return true;
}

/* Checks if a 3x3 cell is valid */
bool cell_valid(int grid[N][N], int row, int col)
{
    int cell [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int r1 = row - row%3;
	int r2 = r1 + 3;
	int c1 = col - col%3;
	int c2 = c1+3;

    for (int i = r1; i < r2; ++i)
		for (int j = c1; j < c2; ++j)
            cell[grid[i][j]]++;

	for (int i = 1; i < 10; ++i)
        if (cell[i] == 0 || cell[i] > 1) return false;

	return true;
}


int main()
{
    int x, prev = 0, row = 0, col = 0, entryCount = 0;
    int grid[N][N];

    /* Sudoku input */
    while ((x = getchar())) {
        if (x == 'EOF') break;

        if (prev == '\n' && x == '\n') {
            if (row == 9 && entryCount == 81) break;
            else {
                cout << "input error, missing row/column?" << endl;
                exit(1);
            }
        }

        int y = x - '0'; // Convert to integer

        if (x == '\n') {
            col = 0;
            row++;
        } else {
            grid[row][col] = y; // insert into sudoku matrix
            col++;
            entryCount++;
        }

        prev = x;
    }


    /* Check if input was ok */
    int rowErr = 0, colErr = 0, cellErr = 0;

    for (int i = 0; i < N; i++) {
        if (!row_valid(grid, i)) rowErr = i+1;
        if (!col_valid(grid, i)) colErr = i+1;
    }

    for (int i = 0; i < 9; i+=3)
        for (int j = 0; j < 9; j+=3)
            if (!cell_valid(grid, i, j)) cellErr = 1;

    if (rowErr || colErr || cellErr) {
        cout << "Not a valid solution row, col: " << rowErr << " ";
        cout << colErr << endl;
    } else cout << "Valid solution" << endl;

    return 0;
}
