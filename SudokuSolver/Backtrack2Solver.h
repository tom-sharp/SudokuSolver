#pragma once

#include"SolverBase.h"
#include"Sudoku.h"
#include"Validate.h"

namespace SudokuPuzzle {


	// the most basic backtracker
	class Backtrack2Solver : public SolverBase {

	public:

		Backtrack2Solver() { this->name = new char[] {"Backtrack2"}; }
		~Backtrack2Solver() { }

		bool Solve(Sudoku* sudoku) {
			if (sudoku == nullptr) return false;
			this->puzzle = sudoku;
			this->workpuzzle.copy(sudoku);
			return this->runsolver();
		}


	private:

		bool runsolver() {
			int pos = 0;
			int ecounter = 0;
			int bcounter = 0;
			char* pz1 = this->puzzle->puzzle();
			char* pz2 = this->workpuzzle.puzzle();

			while (pos >= 0 && pos < this->workpuzzle.SudokuLength) {
				if (pz1[pos] == this->puzzle->Undefined) {

					if (pz2[pos] == this->workpuzzle.Undefined) pz2[pos] = '1';
					else pz2[pos]++;

					if (pz2[pos] > '9') {
						bcounter++;
						pz2[pos] = this->workpuzzle.Undefined;
						while (--pos >= 0) { if (pz1[pos] == this->puzzle->Undefined) break; }
					}
					else { ecounter++; if (this->validate.isvalid(&this->workpuzzle, pos)) pos++; }
				}
				else pos++;
			}
			this->evaluatecounter = ecounter;
			this->backtrackcounter = bcounter;
			if (pos < 0) return false;
			this->puzzle->copy(&this->workpuzzle);
			return true;
		}


		Sudoku* puzzle = nullptr;
		Sudoku workpuzzle;
		Validate validate;
	};



}