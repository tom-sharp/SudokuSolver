#pragma once

#include"Sudoku.h"

namespace SudokuPuzzle {


	static const int bitmaskundefined = 0x0200;
	static const int bitmaskall = 0x03ff;
	static const int bitmaskallnumber = 0x01ff;

	static const int sudokusingles = 9;
	static const int bitmasksudokusingle[sudokusingles] = {
		0b000000001, 0b000000010, 0b000000100, 0b000001000, 0b000010000, 0b000100000, 0b001000000, 0b010000000,
		0b100000000
	};

	static const int sudokupairs = 36;
	static const int bitmasksudokupair[sudokupairs] = {
		0b000000011, 0b000000110, 0b000001100, 0b000011000, 0b000110000, 0b001100000, 0b011000000, 0b110000000,
		0b000000101, 0b000001010, 0b000010100, 0b000101000, 0b001010000, 0b010100000, 0b101000000, 0b000001001,
		0b000010010, 0b000100100, 0b001001000, 0b010010000, 0b100100000, 0b000010001, 0b000100010, 0b001000100,
		0b010001000, 0b100010000, 0b000100001, 0b001000010, 0b010000100, 0b100001000, 0b001000001, 0b010000010,
		0b100000100, 0b010000001, 0b100000010, 0b100000001
	};



	static const int clustercolumncelloffset = 0;
	static const int clusterrowcelloffset = 81;
	static const int clustersquarecelloffset = 162;
	static const int clustercells[243] = { 
		 0,  9, 18, 27, 36, 45, 54, 63, 72,
		 1, 10, 19, 28, 37, 46, 55, 64, 73,
		 2, 11, 20, 29, 38, 47, 56, 65, 74,
		 3, 12, 21, 30, 39, 48, 57, 66, 75,
		 4, 13, 22, 31, 40, 49, 58, 67, 76,
		 5, 14, 23, 32, 41, 50, 59, 68, 77,
		 6, 15, 24, 33, 42, 51, 60, 69, 78,
		 7, 16, 25, 34, 43, 52, 61, 70, 79,
		 8, 17, 26, 35, 44, 53, 62, 71, 80,

		 0,  1,  2,  3,  4,  5,  6,  7,  8,
		 9, 10 ,11, 12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23, 24, 25, 26,
		27,	28, 29, 30, 31, 32, 33, 34, 35,
		36, 37, 38, 39, 40, 41, 42, 43, 44,
		45, 46, 47, 48, 49, 50, 51, 52, 53,
		54, 55, 56, 57, 58, 59, 60, 61, 62,
		63, 64, 65, 66, 67, 68, 69, 70, 71,
		72, 73, 74, 75, 76, 77, 78, 79, 80,

		 0,  1,  2,  9, 10, 11, 18, 19, 20,
		 3,  4,  5, 12, 13, 14, 21, 22, 23,
		 6,  7,  8, 15, 16, 17, 24, 25, 26,
		27, 28, 29, 36, 37, 38, 45, 46, 47,
		30, 31, 32, 39, 40, 41, 48, 49, 50,
		33, 34, 35, 42, 43, 44, 51, 52, 53,
		54, 55, 56, 63, 64, 65, 72, 73, 74,
		57, 58, 59, 66, 67, 68, 75, 76, 77,
		60, 61, 62, 69, 70, 71, 78, 79, 80

	};





class Validate {

public:

	Validate() { }
	~Validate() { }


	// validate all cells
	bool isvalid(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		for(int i = 0; i < sudoku->SudokuLength; i++) if (!this->isvalid(sudoku, i)) return false;
		return true;
	}

	// validate row/column and square for position
	bool isvalid(Sudoku* sudoku, int position) {
		if (sudoku == nullptr) return false;
		char ch = sudoku->get(position);
		if (ch == sudoku->Undefined || ch == 0) return true;
		char* pz = sudoku->puzzle();
		int* cells = nullptr;
		int count = 0;



		/////////////////////////

		int columncluster = position % 9;
		int rowcluster = (position / 9);
		int squarecluster = ((rowcluster / 3) * 3) + (columncluster / 3);

		count = 0;
		cells = getclustercells(columncluster);
		for (int i = 0; i < 9; i++) { if (pz[cells[i]] == ch) count++; }
		if (count > 1) return false;

		count = 0;
		cells = getclustercells(rowcluster + 9);
		for (int i = 0; i < 9; i++) { if (pz[cells[i]] == ch) count++; }
		if (count > 1) return false;

		count = 0;
		cells = getclustercells(squarecluster + 18);
		for (int i = 0; i < 9; i++) { if (pz[cells[i]] == ch) count++; }
		if (count > 1) return false;

		//return true;

		/////////////////////////



		//int count = 0;
		//int colpos = position % 9;
		//int rowpos = position - (position % 9);
		//int squarepos = position - (position % 27) + (colpos - colpos % 3);

		//for(int i = 0; i < 9; i++) { if (pz[colpos] == ch) count++; colpos += 9; }
		//if (count > 1) return false;

		//count = 0;
		//for (int i = 0; i < 9; i++) { if (pz[rowpos] == ch) count++; rowpos++; }
		//if (count > 1) return false;

		//count = 0;
		//for (int i = 0; i < 3; i++) {
		//	for (int j = 0; j < 3 ; j++) {
		//		if (pz[squarepos] == ch) count++; squarepos++;
		//	}
		//	squarepos += 6;
		//}
		//if (count > 1) return false;
		//return true;


	}


	bool issolved(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		char* pz = sudoku->puzzle();
		for(int i = 0; i < sudoku->SudokuLength; i++) {
			if (pz[i] == sudoku->Undefined) return false;
		}
		return this->isvalid(sudoku);
	}

	bool issolvable(Sudoku* sudoku) {
		if (sudoku == nullptr) return false;
		char* pz = sudoku->puzzle();
		for (int i = 0; i < sudoku->SudokuLength; i++) {
			if (pz[i] == sudoku->Undefined && bitmask(sudoku, i) == 0) return false;
		}
		return true;
	}

	bool isunsolvable(Sudoku* sudoku) {
		if (sudoku == nullptr) return true;
		int accumulatedmask = 0;
		char* pz = sudoku->puzzle();
		int* cells = nullptr;
		for (int cluster = 0; cluster < 27; cluster++) {
			cells = this->getclustercells(cluster);
			accumulatedmask = 0;
			for (int pos = 0; pos < 9; pos++) {
				accumulatedmask |= this->bitmask(sudoku, cells[pos]);
			}
			if ((accumulatedmask & bitmaskallnumber) != bitmaskallnumber) return true;
		}
		return false;
	}



	// return bitmask for position. if ther is more than one possible, the undefined biit is set
	// else only the value bit is set.
	// 0 is returned if unsolvable
	int bitmask(Sudoku* sudoku, int position) {
		if (sudoku == nullptr) return 0;
		char* pz = sudoku->puzzle();
		int* cells;
		int bm = 0;
		int mask = 0;
		if ((bm = this->bitmask(pz[position])) != 0x0200) return bm;	// cell is defined

		/////////////////////////
		
		int columncluster = position % 9;
		int rowcluster = (position / 9);
		int squarecluster = ((rowcluster/3) * 3) + (columncluster / 3);

		cells = getclustercells(columncluster);
		for (int i = 0; i < 9; i++) { if ((mask = this->bitmask(pz[cells[i]])) != 0x0200) bm |= mask; }
		cells = getclustercells(rowcluster + 9);
		for (int i = 0; i < 9; i++) { if ((mask = this->bitmask(pz[cells[i]])) != 0x0200) bm |= mask; }
		cells = getclustercells(squarecluster + 18);
		for (int i = 0; i < 9; i++) { if ((mask = this->bitmask(pz[cells[i]])) != 0x0200) bm |= mask; }

		if ((bm ^= bitmaskall) == 0) return bm;	// unsolvable
		if (bitmask(bm) == '.') bm |= bitmaskundefined;	// check if there is only 1 possible
		return bm;

		/////////////////////////



		//int colpos = position % 9;
		//int rowpos = position - (position % 9);
		//int squarepos = position - (position % 27) + (colpos - colpos % 3);

		//for (int i = 0; i < 9; i++) { if ((mask = this->bitmask(pz[colpos])) != 0x0200) bm |= mask; colpos += 9; }
		//for (int i = 0; i < 9; i++) { if ((mask = this->bitmask(pz[rowpos])) != 0x0200) bm |= mask; rowpos++; }

		//for (int i = 0; i < 3; i++) {
		//	for (int j = 0; j < 3; j++) {
		//		if ((mask = this->bitmask(pz[squarepos])) != 0x0200) bm |= mask; squarepos++;
		//	}
		//	squarepos += 6;
		//}
		//if ((bm ^= bitmaskall) == 0) return bm;	// unsolvable
		//if (bitmask(bm) == '.') bm |= bitmaskundefined;	// check if there is only 1 possible
		//return bm;


	}


	int* getclustercells(int clusterid) {
		if (clusterid < 0 || clusterid > 26) return nullptr;
		return (int*)&clustercells[clusterid * 9];
	}


	// return mask for character if value is not defined undefined mask is returned
	int bitmask(char value) {
		switch (value)
		{
		case '1': return 0x0001;
		case '2': return 0x0002;
		case '3': return 0x0004;
		case '4': return 0x0008;
		case '5': return 0x0010;
		case '6': return 0x0020;
		case '7': return 0x0040;
		case '8': return 0x0080;
		case '9': return 0x0100;
		}
		return 0x0200;
	}

	// return character value for mask or undefined character if not defined mask
	char bitmask(int mask) {
		switch (mask)
		{
		case 0x0001: return '1';
		case 0x0002: return '2';
		case 0x0004: return '3';
		case 0x0008: return '4';
		case 0x0010: return '5';
		case 0x0020: return '6';
		case 0x0040: return '7';
		case 0x0080: return '8';
		case 0x0100: return '9';
		}
		return '.';
	}




private:


	//void setupclustercells() {

	//	if (this->allclustercells == nullptr) this->allclustercells = new int[243]();

	//	int pos = 0, cell = 0;

	//	// setup column cluster cells
	//	for (int i = 0; i < 9; i++) {
	//		cell = i;
	//		for (int j = 0; j < 9; j++) { this->allclustercells[pos++] = cell; cell += 9; }
	//	}

	//	// setup row cluster cells
	//	for (int i = 0; i < 9; i++) {
	//		cell = i * 9;
	//		for (int j = 0; j < 9; j++) { this->allclustercells[pos++] = cell; cell++; }
	//	}

	//	// setup square cluster cells
	//	for (int i = 0; i < 9; i++) {
	//		cell = this->squarestart[i];
	//		for (int j = 0; j < 3; j++) {
	//			for (int k = 0; k < 3; k++) { this->allclustercells[pos++] = cell; cell++; }
	//			cell += 6;
	//		}
	//	}
	//}
	//int* allclustercells;
	//int squarestart[9] = { 0, 3, 6, 27, 30, 33, 54, 57, 60 };



};

}
