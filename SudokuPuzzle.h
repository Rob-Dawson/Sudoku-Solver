#pragma once
#include "CellGroup.h"
#include <iostream>
#include <fstream>
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle();
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);
	void SolvePuzzle();
	void RowCandidates()const;
	void ColumnCandidates()const;
	void BlockCandidates()const;
	void CandidateList();
	void NakedSingle();
	void Update(int rows, int columns, int temp)const;
private:
	void Output() const;
	void InitialiseGrid();

	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlocks[9];

	int m_loops = 0;
	int m_candidateValueConsidered = 0;
	int m_answered = 0;
};

