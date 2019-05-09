#include <iostream>
#include <cassert>
#include "grid_alias.h"
#include "sudoku_io.h"
#include <math.h> 

/**
  Check whether a number could be placed at the specified row and column,
  according to the Sudoku rules.
  The function assumes sudoku[row][col] does not contain any value yet (= 0).
  This function reads from the `sudoku` vector, but never modifies its content.

  @param sudoku					 a sudoku grid
  @param num					 a number from 1 to sudoku.size()
  @param row					 index of the row (0 to sudoku.size()-1)
  @param col					 index of the column (0 to sudoku.size()-1)
  @return bool true				 if num is valid in (row, col)
*/
bool isValid(const grid& sudoku, int num, int row, int col) {
	// PRE:
	assert(sudoku[row][col] == 0);
	assert(row >= 0 && row < (int)sudoku.size());
	assert(col >= 0 && col < (int)sudoku.size());
	assert(num >= 1 && num <= (int)sudoku.size());

	unsigned int counter = 0;

	for (unsigned int r = 0; r < sudoku.size(); r++) {
		if (sudoku[r][col] == num)
			counter++;
	}

	for (unsigned int c = 0; c < sudoku.size(); c++) {
		if (sudoku[row][c] == num)
			counter++;
	}
	
	// check subgrids
	int subgrid_size = sqrt(sudoku.size());
	unsigned int subgrid_hori = 0;
	unsigned int subgrid_vert = 0;

	for (int subgrid_start = 0; subgrid_start < (int)sudoku.size(); subgrid_start += subgrid_size) {
		if (row >= subgrid_start && row < (subgrid_start + subgrid_size)) {
			subgrid_hori = subgrid_start;
		}
		if (col >= subgrid_start && col < (subgrid_start + subgrid_size)) {
			subgrid_vert = subgrid_start;
		}
	}

	for (unsigned int r = subgrid_hori; r < (subgrid_hori + subgrid_size); r++) {
		for (unsigned int c = subgrid_vert; c < (subgrid_vert + subgrid_size); c++) {
			if (sudoku[r][c] == num) {
				counter++;
			}
		}
	}
	
	return (counter <= 0);
}

/**
  Tries to put a valid number into the specified cell (using 'isValid').
  If a valid number has been found, it calls itself on a next cell recursively.
  If that recursive call returns FALSE, it tries to find a different valid
  number for the current cell and starts a new recursion (Backtracking step).

  @param sudoku			a sudoku grid
  (@param num			number to verify (1 to sudoku.size()))
  @param row			index of the row (0 to sudoku.size()) (row == sudoku.size() implies
						that the end has been reached. That is, it returns 'true')
  @param col			index of the column (0 to sudoku.size()-1)
  @return bool true		if successfully put a number in the current cell and
						successfully called itself on subsequent cells; false otherwise
*/
bool fillValidNumber(grid& sudoku, int row, int col) {
	// PRE:
	assert(row >= 0 && row <= (int)sudoku.size());
	assert(col >= 0 && col < (int)sudoku.size());
		
	for (int r = row; r < (int)sudoku.size(); r++) {
		for (int c = col; c < (int)sudoku.size(); c++) {
			if (sudoku[r][c] != 0) {
				continue;
			}
			for (unsigned int num = 1; num <= sudoku.size(); num++) {
				if (isValid(sudoku, num, r, c)) {
					sudoku[r][c] = num;
					// Remove later:
					printSudoku(sudoku);
					
					if (col == (int)sudoku.size() - 1) {
						// Termination condition, or so I thought.
						if (row == sudoku.size() - 1) {
							return true;
						}
						fillValidNumber(sudoku, row + 1, 0);
					}
					if (!fillValidNumber(sudoku, row, col + 1)) {
						sudoku[r][c] = 0;
					}
					// Termination condition:
					if (col == (int)sudoku.size() - 1 && row == sudoku.size() - 1) {
						return true;
					}
				}
			}
			return false; // backtrack
		}
		col = 0;
	}
	return false;
}


int main() {
	// Choose the size of sudoku matrix
	int size = 0;
	while (size != 4 && size != 9) {
		std::cout << "Choose the size of sudoku grid (4 or 9):";
		std::cin >> size;
	}
	// Store the Sudoku as 2D vector (row-wise).
	// sudoku[i][j] refer to cell at row i and column j.
	grid sudoku(size, std::vector<int>(size, 0));
	
	// Call util function to fill sudoku array with some input
	std::cout << "Enter sudoku:\n";
	readSudokuFromInput(sudoku);
	
	// Solve by starting from first cell in the grid
	bool isSolved = fillValidNumber(sudoku,0,0);

	// Print out the sudoku in its current state
	std::cout << "\nFINAL RESULT" << std::endl; // solver result after this string
	if(isSolved) {
	  printSudoku(sudoku);
	} else {
	  std::cout << "No solution found." << std::endl;
	}
	return 0;
	
}

