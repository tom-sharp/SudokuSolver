#pragma once

#include "SolverBase.h"
#include"Sudoku.h"
#include"Validate.h"
#include "SudokuMask.h"

namespace SudokuPuzzle {


// backtracker only testing qualified numbers
class BacktrackQSolver : public SolverBase {

public:

	BacktrackQSolver() { this->workpuzzle = new Sudoku(); this->puzzlemask = new SudokuMask(); this->name = new char[] {"Backtrack, filtered"}; }
	~BacktrackQSolver() { if (this->workpuzzle != nullptr) delete this->workpuzzle; if (this->puzzlemask != nullptr) delete this->puzzlemask; }

	bool Solve(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		this->puzzle = sudoku;
		this->workpuzzle->copy(sudoku);
		this->puzzlemask->setupmask(sudoku);
		return this->runsolver();
	}

private:

	bool runsolver() {
		int pos = 0;
		int ecounter = 0;
		int bcounter = 0;
		char* pz1 = this->puzzle->puzzle();
		char* pz2 = this->workpuzzle->puzzle();

		while (pos >= 0 && pos < this->workpuzzle->SudokuLength) {
			if (pz1[pos] == this->puzzle->Undefined) {

				pz2[pos] = this->puzzlemask->nextchar(pos, pz2[pos]);

				if (pz2[pos] == this->workpuzzle->Undefined) {
					bcounter++;
					while (--pos >= 0) { if (pz1[pos] == this->puzzle->Undefined) break; }
				}
				else { ecounter++; if (this->validate.isvalid(this->workpuzzle, pos)) pos++; }
			}
			else pos++;
		}
		this->evaluatecounter = ecounter;
		this->backtrackcounter = bcounter;
		if (pos < 0) return false;
		this->puzzle->copy(this->workpuzzle);
		return true;
	}


	Sudoku* puzzle = nullptr;
	Sudoku* workpuzzle = nullptr;
	Validate validate;
	SudokuMask* puzzlemask = nullptr;

};


}
