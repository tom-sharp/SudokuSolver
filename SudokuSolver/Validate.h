#pragma once

#include"Sudoku.h"

namespace SudokuPuzzle {

class Validate {

public:

	// validate all cells
	bool IsValid(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		for(int i = 0; i < sudoku->SudokuLength; i++) if (!this->IsValid(sudoku, i)) return false;
		return true;
	}

	// validate row/column and square for position
	bool IsValid(Sudoku* sudoku, int position) {
		if (sudoku == nullptr) return false;
		char ch = sudoku->get(position);
		if (ch == sudoku->Undefined || ch == 0) return true;
		char* pz = sudoku->puzzle();

		int count = 0;
		int colpos = position % 9;
		int rowpos = position - (position % 9);
		int squarepos = position - (position % 27) + (colpos - colpos % 3);

		for(int i = 0; i < 9; i++) { if (pz[colpos] == ch) count++; colpos += 9; }
		if (count > 1) return false;


		count = 0;
		for (int i = 0; i < 9; i++) { if (pz[rowpos] == ch) count++; rowpos++; }
		if (count > 1) return false;

		count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3 ; j++) {
				if (squarepos < 0 || squarepos > 80) throw;
				if (pz[squarepos] == ch) count++; squarepos++;
			}
			squarepos += 6;
		}
		if (count > 1) return false;

		return true;
	}

	// validate row/column and square for position: row column
	bool IsValid(Sudoku* sudoku, int row, int column) {
		return false;
	}

	bool IsSolved(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		char* pz = sudoku->puzzle();
		for(int i = 0; i < sudoku->SudokuLength; i++) {
			if (pz[i] == sudoku->Undefined) return false;
		}
		return this->IsValid(sudoku);
	}

private:


};

}
