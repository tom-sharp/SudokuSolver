#pragma once

#include"Sudoku.h"
#include"Validate.h"

namespace SudokuPuzzle {




class BacktrackSolver {

public:

	BacktrackSolver() { this->workpuzzle = new Sudoku();}
	~BacktrackSolver() { if (this->workpuzzle != nullptr) delete this->workpuzzle; }

	// the most basic backtracker
	bool Solve(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		this->puzzle = sudoku;
		this->workpuzzle->copy(sudoku);
		return this->runsolver();
	}

private:

	bool runsolver() {
		int pos = 0;
		char* pz1 = this->puzzle->puzzle();
		char* pz2 = this->workpuzzle->puzzle();

		while (pos >= 0 && pos < this->workpuzzle->SudokuLength) {
			if (pz1[pos] == this->puzzle->Undefined) {
				if (pz2[pos] == this->workpuzzle->Undefined) pz2[pos] = '1';
				else pz2[pos]++;
				if (pz2[pos] > '9') {
					pz2[pos] = this->workpuzzle->Undefined;
					while(--pos >= 0) {if (pz1[pos] == this->puzzle->Undefined) break; }
				}
				else if (this->validate.IsValid(this->workpuzzle)) pos++;
				printf("%s\r", pz2);
			}
			else pos++;
		}
		if (pos < 0) return false;
		this->puzzle->copy(this->workpuzzle);
		return true;
	}

	Sudoku* puzzle = nullptr;
	Sudoku* workpuzzle = nullptr;
	Validate validate;
};



}