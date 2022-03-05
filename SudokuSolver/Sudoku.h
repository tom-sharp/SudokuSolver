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

	Sudoku* puzzle(char* puzzlestring) {
		if (puzzlestring == nullptr) { this->clear(); return this; }
		int pos1 = 0, pos2 = 0;
		while (puzzlestring[pos1] != 0) {
			switch (puzzlestring[pos1]) {
			case '.':
			case '0':
			case 'x':
			case 'X':
				this->ptrSudoku[pos2++] = this->Undefined;
				break;
			default:
				if (puzzlestring[pos1] >= '1' && puzzlestring[pos1] <= '9') {
					this->ptrSudoku[pos2++] = puzzlestring[pos1];
				}
				break;
			}
			pos1++;
			if (pos2 >= this->SudokuLength) break;
		}
		while (pos2 < this->SudokuLength) this->ptrSudoku[pos2++] = this->Undefined;
		return this;
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

	// return number of occurances for character in puzzle
	int count(char character) {
		int counter = 0;
		if (this->ptrSudoku == nullptr) return counter;
		for (int i = 0; i < this->SudokuLength; i++) if (this->ptrSudoku[i] == character) counter++;
		return counter;
	}



	const int SudokuLength = 81;
	const char Undefined = '.';

private:
	
	char* ptrSudoku = nullptr;

};

}
