#pragma once

#include"Sudoku.h"
#include"SolverHelp.h"
#include"Validate.h"

namespace SudokuPuzzle {


class Solver {

public:

	Solver() {
		this->puzzle = new Sudoku();
	}
	~Solver() {
		if (this->puzzle != nullptr) delete this->puzzle;
	}

	void Run(int argc, char* argv[]) {


		if (!this->checkargs(argc, argv)) {
			printf("Invalid arguments -? for help\n");
			return;
		}
		if (this->inputstring != nullptr) this->setpuzzle(this->inputstring);		
		printf("%s\n", this->puzzle->puzzle());
		if (!this->validate.IsValid(this->puzzle)) {
			printf("puzzle is invalid\n");
			return;
		}


		// code to solve


	}

private:

	bool checkargs(int argc, char* argv[]) {
		SolverHelp help;
		int count = 1;
		while (count < argc) {
			if (argv[count][0] == '-') {

				if (argv[count][1] == '?') { help.ShowHelp(); exit(0); }
				else if (argv[count][1] == '1') { this->inputstring = (char*)demopuzzle1; }
				else if (argv[count][1] == '2') { this->inputstring = (char*)demopuzzle2; }
				else if (argv[count][1] == '3') { this->inputstring = (char*)demopuzzle3; }
				else return false;

			}
			else this->inputstring = argv[count];
			count++;
		}
		return true;
	}

	void setpuzzle(char* puzzlestring) {
		this->puzzle->clear();
		if (puzzlestring == nullptr) return;
		int pos1 = 0, pos2 = 0;
		while (puzzlestring[pos1] != 0) {
			switch (puzzlestring[pos1]) {
				case '.':
				case '0':
				case 'x':
				case 'X':
					this->puzzle->set(pos2++, this->puzzle->Undefined);
					break;
				default:
					if (puzzlestring[pos1] >= '1' && puzzlestring[pos1] <= '9') {
						this->puzzle->set(pos2++, puzzlestring[pos1]);
					}
					break;
			}
			pos1++;
			if (pos2 >= this->puzzle->SudokuLength) break;
		}
		while (pos2 < this->puzzle->SudokuLength) {
			this->puzzle->set(pos2++, this->puzzle->Undefined);
		}
	}

	char* inputstring = nullptr;
	Sudoku* puzzle = nullptr;
	Validate validate;
};


}
