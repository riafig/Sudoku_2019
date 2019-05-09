#include <iostream>
#include "sudoku_io.h"
#include <math.h> 

void printSudoku(const grid& sudoku) {
	int size = sudoku.size();
	int subgrid_size = sqrt(size);
	int tmp = (size + sqrt(size) + 1) * 2 - 1;

	for (int k = 0; k < tmp; k++)
		std::cout << "-";
	std::cout << std::endl;

	// output the sudoku nicely
	for (int i = 0; i < size; ++i) {
		std::cout << "| ";
		for (int j = 0; j < size; ++j) {
			int n = sudoku[i][j];
			if (n == 0) {
				std::cout << "- ";
			}
			else {
				std::cout << n << " ";
			}

			if ((j + 1) % subgrid_size == 0) {
				std::cout << "| ";
			}
		}
		std::cout << std::endl;

		if ((i + 1) % subgrid_size == 0) {
			for (int k = 0; k < tmp; k++)
				std::cout << "-";
			std::cout << std::endl;
		}
	}
}

void readSudokuFromInput(grid & sudoku) {
	for (unsigned i = 0; i < sudoku.size(); ++i) {
		for (unsigned j = 0; j < sudoku.size(); ++j) {
			std::cin >> sudoku[i][j];
		}
	}
}
