#pragma once

#include "SolverBase.h"
#include"Sudoku.h"
#include"Validate.h"
#include"SudokuMask.h"

namespace SudokuPuzzle {






class RulesSolver : public SolverBase {

public:

	RulesSolver() { this->name = new char[] {"Logic"};  }
	~RulesSolver() { }


	bool Solve(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		this->puzzle = sudoku;
		return this->runsolver();
	}


private:

	bool runsolver() {
		bool run = true;
		int mask = 0;
		char ch = 0;
		char* pz = this->puzzle->puzzle();
		while(run) {
			run = this->ResolveSingles();
			if (!run) run = ResolveClusterSingleCells();
		}
		if (this->validate.issolved(this->puzzle)) return true;
		return false;
	}


	bool ResolveSingles() {
		char* pz = this->puzzle->puzzle();
		int mask = 0;
		char ch = 0;
		bool ret = false;
		for (int i = 0; i < this->puzzle->SudokuLength; i++) {
			if (pz[i] == this->puzzle->Undefined) {
				if ((mask = this->validate.bitmask(this->puzzle, i)) == 0) return false;
				if ((ch = this->validate.bitmask(mask)) != this->puzzle->Undefined) {
					pz[i] = ch; ret = true;
				}
			}
		}
		return ret;
	}

	bool ResolveClusterSingleCells() {
		char* pz = this->puzzle->puzzle();
		int mask = 0;
		char ch = 0;
		bool ret = false;
		int* cells = nullptr;
		int accumulatedmask = 0, filtermask = 0, singlemask = 0;
		for (int cluster = 0; cluster < 27; cluster++) {
			cells = this->validate.getclustercells(cluster);
			accumulatedmask = 0, filtermask = 0, singlemask = 0;
			for (int pos = 0; pos < 9; pos++) {
				if (pz[cells[pos]] == this->puzzle->Undefined) {
					if ((mask = this->validate.bitmask(this->puzzle, cells[pos])) == 0) return false;
					filtermask |= accumulatedmask & mask;	// all possibles occuring at least twice
					accumulatedmask |= mask;				// all possibles occuring in cluster
				}
			}
			if ((singlemask = (accumulatedmask ^ filtermask) & bitmaskallnumber) != 0) {
				for (int pos = 0; pos < 9; pos++) {
					if (pz[cells[pos]] == this->puzzle->Undefined) {
						if ((mask = this->validate.bitmask(this->puzzle, cells[pos])) == 0) return false;
						if ((ch = this->validate.bitmask(mask & singlemask)) != this->puzzle->Undefined) {
							pz[cells[pos]] = ch;
							ret = true;
						}
					}
				}
			}
		}
		return ret;
	}



	Sudoku* puzzle = nullptr;
	Validate validate;


};






}
