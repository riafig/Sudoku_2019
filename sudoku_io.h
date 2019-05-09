#pragma once

#ifndef SUDOKU_IO
#define SUDOKU_IO
#include "grid_alias.h"

void printSudoku(const grid& sudoku);

void readSudokuFromInput(grid& sudoku);

#endif