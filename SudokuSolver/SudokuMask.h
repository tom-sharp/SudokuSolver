#pragma once
#include "Validate.h"


namespace SudokuPuzzle {


class SudokuMask {


public:

	SudokuMask() { }
	~SudokuMask() { if (this->mask != nullptr) delete[] this->mask; }

	SudokuMask* setupmask(Sudoku* sudoku) {
		if (sudoku == nullptr) return this;
		if (this->masksize != sudoku->SudokuLength) {
			if (this->mask != nullptr) delete [] this->mask;
			this->mask = nullptr;
			this->masksize = sudoku->SudokuLength;
			if (this->masksize > 0) this->mask = new int[this->masksize]();
		}
		int pos = 0;
		while (pos < this->masksize) {
			this->mask[pos] = this->validate.bitmask(sudoku, pos);
			pos++;
		}
		return this;
	}


	char nextchar(int pos, char current) {
		if (this->mask == nullptr) return this->validate.bitmask(0);
		int currentbit = this->validate.bitmask(current);
		if (currentbit == bitmaskundefined) currentbit = 0x0001;
		else currentbit <<= 1;
		while (currentbit != bitmaskundefined) {
			if ((currentbit & this->mask[pos]) != 0x0000) return this->validate.bitmask(currentbit);
			currentbit <<= 1;
		}
		return this->validate.bitmask(0);
	}




private:

	int* mask = nullptr;
	int masksize = 0;
	Validate validate;
	int numbercount[10] = { 0 };


};



}
