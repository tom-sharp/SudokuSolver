#pragma once

#include"Sudoku.h"
#include"SolverHelp.h"
#include"Validate.h"
#include"RulesSolver.h"
#include"BacktrackSolver.h"
#include"Backtrack2Solver.h"
#include"BacktrackQSolver.h"
#include"NumpassSolver.h"
#include"CSysCore.h"
#include"StopWatch.h"

using namespace SysCore;

namespace SudokuPuzzle {


class Solver {

public:

	Solver() {
		this->puzzle = new Sudoku();
		this->puzzles = new CList();
		this->puzzles->isManaged(true);
	}
	~Solver() {
		if (this->puzzle != nullptr) delete this->puzzle;
		if (this->solver != nullptr) delete this->solver;
		if (this->puzzles != nullptr) delete this->puzzles;
	}

	void Run(int argc, char* argv[]) {

		int sumsolved = 0, suminvalid = 0, sumnotsolved = 0;
		if (!this->checkargs(argc, argv)) {
			printf("Invalid arguments -? for help\n");
			return;
		}


		// set the choosen solve puzzle algorithm  - or use the default if none is choosen
		if (this->solver != nullptr) { delete this->solver; this->solver = nullptr; }
		if (this->OptBackTrack) this->solver = new BacktrackSolver();
		else if (this->OptBackTrackQ) this->solver = new BacktrackQSolver();
		else if (this->OptBackTrack2) this->solver = new Backtrack2Solver();
		else if (this->OptNumpass) this->solver = new NumpassSolver();
		else if (this->OptLogicRule) this->solver = new RulesSolver();
		else this->solver = new NumpassSolver(); // default


		if (!this->getpuzzles()) {
			printf("could not read file %s\n", this->inputstring);
			return;
		}

		Misc::StopWatch t1; t1.start();

		// loop through all puzzles
		CStr* pz = (CStr*)this->puzzles->getfirst();
		while (pz != nullptr) {
			this->puzzle->puzzle(pz->str());
			printf("%s", this->puzzle->puzzle());
			if (this->solvepuzzle()) {
				printf(" - start puzzle\n");
				printf("%s - solved (ev %i | bt %i)\n", this->puzzle->puzzle(), solver->evaluatecounter, solver->backtrackcounter);
				sumsolved++;
			}
			else if (!this->validate.isvalid(this->puzzle)) { printf(" - invalid\n"); suminvalid++; }
			else if (!this->validate.issolvable(this->puzzle) || this->validate.isunsolvable(this->puzzle)) { printf(" - unsolvable\n"); suminvalid++; }
			else { printf(" - could not solve\n"); sumnotsolved++; }
			pz = (CStr*)this->puzzles->getnext();
		}
		t1.stop();

		printf("Summary: ");
		if (sumsolved > 0)  printf("%i solved   ", sumsolved);
		if (sumnotsolved > 0)  printf("%i not solved   ", sumnotsolved);
		if (suminvalid > 0)  printf("%i invalid", suminvalid);
		printf(" time %.3f sec (%s)\n", t1.time(), solver->name);
	}


private:

	bool checkargs(int argc, char* argv[]) {
		SolverHelp help;
		CStr arg;
		int count = 1;
		while (count < argc) {
			arg.str(argv[count])->tolower();
			if (arg.isEqual("-?")) { help.ShowHelp(); exit(0); }
			else if (arg.isEqual("-1")) { this->inputstring = (char*)demopuzzle1; }
			else if (arg.isEqual("-2")) { this->inputstring = (char*)demopuzzle2; }
			else if (arg.isEqual("-3")) { this->inputstring = (char*)demopuzzle3; }
			else if (arg.isEqual("-bt")) { this->OptBackTrack = true; }
			else if (arg.isEqual("-b2")) { this->OptBackTrack2 = true; }
			else if (arg.isEqual("-bq")) { this->OptBackTrackQ = true; }
			else if (arg.isEqual("-np")) { this->OptNumpass = true; }
			else if (arg.isEqual("-l")) { this->OptLogicRule = true; }
			else if (arg.isEqual("-f")) { this->OptReadFile = true; }
			else if (arg.isEqual("-fr")) { this->OptReadFile = true; this->OptReadFileMulti = true; }
			else if (arg.constains('?') || arg.constains('*')) { help.ShowHelp(); exit(0); }
			else if (argv[count][0] == '-') { printf("invalid option %s\n", arg.str()); exit(0); }
			else this->inputstring = argv[count];
			count++;
		}
		return true;
	}

	bool getpuzzles() {
		CStr* pzstr = nullptr;
		char ch;
		this->puzzles->clear();
		if (this->OptReadFile) {
			CStream fstream;
			if (fstream.OpenStream(CStream::StreamMode::ReadFile, this->inputstring) != 0) return false;
			while (fstream.BytesToRead() > 0) {
				if (this->OptReadFileMulti) {
					pzstr = new CStr(fstream.GetLine());
					if (pzstr->isEmpty()) delete pzstr;
					else if (pzstr->size() > 300) { delete pzstr; fstream.CloseStream(); return false; }
					else this->puzzles->add(pzstr);
				}
				else {
					if (pzstr == nullptr) pzstr = new CStr(81);
					ch = fstream.GetChar();
					if (ch >= '1' && ch <= '9') pzstr->append(ch);
					else if (ch == '.' || ch == '0' || ch=='x' || ch=='X') pzstr->append('.');
					if (pzstr->strlen() == 81) break;
				}
			}
			fstream.CloseStream();
			if (!this->OptReadFileMulti) this->puzzles->add(pzstr);
		}
		else {
			if (this->inputstring != nullptr) this->puzzles->add(new CStr(this->inputstring));
			else this->puzzles->add(new CStr(""));
		}
		return true;
	}


	bool solvepuzzle() {
		if (!this->validate.isvalid(this->puzzle)) return false;
		if (!this->validate.issolvable(this->puzzle)) return false;
		if (this->solver->Solve(this->puzzle) && this->validate.issolved(this->puzzle)) return true;
		return false;
	}

	SolverBase* solver = nullptr;
	char* inputstring = nullptr;
	CList* puzzles = nullptr;
	Sudoku* puzzle = nullptr;
	Validate validate;
	bool OptBackTrack = false;
	bool OptBackTrack2 = false;
	bool OptBackTrackQ = false;
	bool OptLogicRule = false;
	bool OptNumpass = false;
	bool OptReadFile = false;
	bool OptReadFileMulti = false;
};


}
