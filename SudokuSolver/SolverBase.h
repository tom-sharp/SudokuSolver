#pragma once

#include"Sudoku.h"

namespace SudokuPuzzle {


class SolverBase {

public:

	SolverBase() { this->evaluatecounter = 0; this->backtrackcounter = 0; this->name = nullptr; }
	~SolverBase() { if (this->name != nullptr) delete this->name; }

	// solver name
	char* name;

	// solving algorithm
	bool virtual Solve(Sudoku* sudoku) = 0;

	// number of tested puzzles
	int evaluatecounter;

	// number of backtracks
	int backtrackcounter;

};

}
