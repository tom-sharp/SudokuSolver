#pragma once

#include "SolverBase.h"
#include"Sudoku.h"
#include"Validate.h"
#include "SudokuMask.h"
#include"RulesSolver.h"

// backtracking starting with lowest number of unknown defined number
namespace SudokuPuzzle {

class NumpassSolver : public SolverBase {

public:

	NumpassSolver() { this->workpuzzle = new Sudoku(); this->numpasspuzzle = new Sudoku(); this->puzzlemask = new SudokuMask(); this->name = new char[] {"Numpass"}; }
	~NumpassSolver() { if (this->workpuzzle != nullptr) delete this->workpuzzle; if (this->numpasspuzzle != nullptr) delete this->numpasspuzzle; if (this->puzzlemask != nullptr) delete this->puzzlemask; }

	bool Solve(Sudoku* sudoku) {
		this->evaluatecounter = 0;
		this->backtrackcounter = 0;
		if (sudoku == nullptr) return false;
		this->puzzle = sudoku;
		if (logicsolver.Solve(this->puzzle)) return true;
		else if (!this->validate.isvalid(this->puzzle) || this->validate.isunsolvable(this->puzzle)) return false;
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
				else { 
					ecounter++; 
					if (this->validate.isvalid(workpuzzle, pos)) {
						if (logicsolver.Solve(this->numpasspuzzle->copy(this->workpuzzle))) {
							this->workpuzzle->copy(this->numpasspuzzle);
							break;
						}
						if (this->validate.issolvable(numpasspuzzle) && this->validate.isvalid(numpasspuzzle)) pos++;
					}
				}
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
	Sudoku* numpasspuzzle = nullptr;
	Validate validate;
	SudokuMask* puzzlemask = nullptr;
	RulesSolver logicsolver;


};

}
