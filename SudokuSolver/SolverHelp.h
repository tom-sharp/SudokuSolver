#pragma once

#include <stdio.h>


namespace SudokuPuzzle {

static const char* demopuzzle1 = "43.....8..1....459....69...12..46....472..91........3..5....7.28...3..919625.....";
static const char* demopuzzle2 = "4..2....9..9..8..7.6...7.5332.1567..1.....4..................268..9.........3....";
static const char* demopuzzle3 = "3.............9.....94..2...13..5..7.5...7.4.6....4.2354..931..8..7.........82...";



static const char* Solver_help[] { 
	"SudokuSolver 0.1 (cpp)",
	"usage sudokusolver puzzlestring",
	"   ",
	"",
};



class SolverHelp {

public:
		void ShowHelp() {
			int line = 0;
			while (Solver_help[line][0] != 0) {
				printf("%s\n", Solver_help[line++]);
			}
		}
private:

};

}