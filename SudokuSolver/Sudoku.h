#pragma once

#include <memory>


namespace SudokuPuzzle {


class Sudoku {

public:

	Sudoku() {
		this->clear();
	}
	~Sudoku() {
		if (this->ptrSudoku != nullptr) delete[] this->ptrSudoku;
	}

	char* puzzle() {
		return this->ptrSudoku;
	}

	Sudoku* clear() {
		if (this->ptrSudoku == nullptr) this->ptrSudoku = new char[this->SudokuLength + 1]();
		memset(this->ptrSudoku, this->Undefined, this->SudokuLength);
		this->ptrSudoku[this->SudokuLength] = 0;
		return this;
	}

	Sudoku* copy(Sudoku* sudoku) {
		if (sudoku == nullptr || sudoku->ptrSudoku == nullptr) return this->clear();
		if (this->ptrSudoku == nullptr) return this->clear();
		memcpy(this->ptrSudoku, sudoku->ptrSudoku, this->SudokuLength);
		this->ptrSudoku[this->SudokuLength] = 0;
		return this;
	}

	Sudoku* clone() {
		Sudoku* sudoku = new Sudoku();
		return sudoku->copy(this);
	}

	Sudoku* set(int pos, char value) {
		if (this->ptrSudoku == nullptr) return this;
		if (pos < 0 || pos >= this->SudokuLength) return this;
		this->ptrSudoku[pos] = value;
		return this;
	}

	Sudoku* set(int row, int column, char value) {
		if (this->ptrSudoku == nullptr) return this;
		if (row < 0 || row > 8 || column < 0 || column > 8) return this;
		int pos = (row * 9) + column;
		this->ptrSudoku[pos] = value;
		return this;
	}

	char get(int pos) {
		if (this->ptrSudoku == nullptr) return 0;
		if (pos < 0 || pos >= this->SudokuLength) return 0;
		return this->ptrSudoku[pos];
	}


	const int SudokuLength = 81;
	const char Undefined = '.';

private:
	
	char* ptrSudoku = nullptr;
};

}
