#include "SudokuPuzzle.h"
#include <Windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
SudokuPuzzle::SudokuPuzzle()
{
}

SudokuPuzzle::~SudokuPuzzle(void)
{
}
void SudokuPuzzle::InitialiseGrid()
{

	ifstream fin("sudoku_puzzle.txt");
	if (fin.is_open())
	{
		int value = 0;

		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				fin >> (value);
				Cell* cell = new Cell(value);
				m_gridRows[row].setCell(column, cell); //Initalise Rows
				m_gridColumns[column].setCell(row, cell); //Initalise Columns		

														  //Initalise block 1 - 3 
				if ((row >= 0) && (row < 3))
				{
					if ((column >= 0) && (column < 3))
					{
						m_gridBlocks[0].setCell(column + (row * 3), cell); //Block 1
					}

					else if ((column >= 3) && (column < 6))
					{
						m_gridBlocks[1].setCell(column - 3 + (row * 3), cell); //Block 2
					}

					else if ((column >= 6) && (column < 9))
					{
						m_gridBlocks[2].setCell(column - 6 + (row * 3), cell); //Block 3
					}
				}

				//Initalise block 4 - 6
				else if ((row >= 3) && (row < 6))
				{
					if ((column >= 0) && (column < 3))
					{
						m_gridBlocks[3].setCell(column - 9 + (row * 3), cell); //Block 4
					}

					else if ((column >= 3) && (column < 6))
					{
						m_gridBlocks[4].setCell(column - 12 + (row * 3), cell); //Block 5
					}

					else if ((column >= 6) && (column < 9))
					{
						m_gridBlocks[5].setCell(column - 15 + (row * 3), cell); //Block 6
					}
				}


				else if ((row >= 6) && (row < 9)) //Initalise block 7 - 9
				{
					if ((column >= 0) && (column < 3))
					{
						m_gridBlocks[6].setCell(column - 18 + (row * 3), cell); //Block 7
					}

					else if ((column >= 3) && (column < 6))
					{
						m_gridBlocks[7].setCell(column - 21 + (row * 3), cell); //Block 8
					}

					else if ((column >= 6) && (column < 9))
					{
						m_gridBlocks[8].setCell(column - 24 + (row * 3), cell); //Block 9
					}
				}
			} //End of inner for-loop
		} //End of outter for-loop
	} //End of outter if-statement
	fin.close();
}

void SudokuPuzzle::SolvePuzzle()
{
	for (int i = 0; i < 81; ++i)
	{
		RowCandidates();
		ColumnCandidates();
		BlockCandidates();
		CandidateList();
		NakedSingle();
		m_loops++;
	}
}

void SudokuPuzzle::NakedSingle()
{

	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			Cell *cell = m_gridRows[row].getRowCell(column);
			vector<int> candidates = cell->getCandidateList();
			if (candidates.size() == 1)
			{
				int temp = candidates[0];
				cell->setValue(temp);
				cell->canidatePointerRemove(temp);
				cell->setCandidateList(candidates);
				Update(row, column, temp);
				m_answered++;
			}
		}
	}

}


void SudokuPuzzle::Update(int rows, int columns, int temp)const
{
	Cell *blockCell;
	for (int row = 0; row < 9; ++row)
	{
		Cell *rowCell = m_gridRows[rows].getRowCell(row);
		vector<int> candidateUpdate = rowCell->getCandidateList();
		if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
		{
			candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
			rowCell->setCandidateList(candidateUpdate);
		}
	}

	for (int column = 0; column < 9; ++column)
	{
		Cell *columnCell = m_gridColumns[columns].getRowCell(column);
		vector<int> candidateUpdate = columnCell->getCandidateList();
		if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
		{
			candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
			columnCell->setCandidateList(candidateUpdate);
		}
	}


	for (int i = 0; i < 9; ++i)
	{
		if ((rows >= 0) && (rows < 3))
		{
			if ((columns >= 0) && (columns < 3))
			{
				blockCell = m_gridBlocks[0].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}

			else if ((columns >= 3) && (columns < 6))
			{
				blockCell = m_gridBlocks[1].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}

			else if ((columns >= 6) && (columns < 9))
			{
				blockCell = m_gridBlocks[2].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}
		}

		else if ((rows >= 3) && (rows < 6))
		{
			if ((columns >= 0) && (columns < 3))
			{
				blockCell = m_gridBlocks[3].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}

			else if ((columns >= 3) && (columns < 6))
			{
				blockCell = m_gridBlocks[4].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}

			else if ((columns >= 6) && (columns < 9))
			{
				blockCell = m_gridBlocks[5].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}
		}

		else if ((rows >= 6) && (rows < 9))
		{
			if ((columns >= 0) && (columns < 3))
			{
				blockCell = m_gridBlocks[6].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}

			else if ((columns >= 3) && (columns < 6))
			{
				blockCell = m_gridBlocks[7].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}

			else if ((columns >= 6) && (columns < 9))
			{
				blockCell = m_gridBlocks[8].getRowCell(rows);
				vector<int> candidateUpdate = blockCell->getCandidateList();
				if (find(candidateUpdate.begin(), candidateUpdate.end(), temp) != candidateUpdate.end())
				{
					candidateUpdate.erase(remove(candidateUpdate.begin(), candidateUpdate.end(), temp));
					blockCell->setCandidateList(candidateUpdate);
				}
			}
		}
	}
	/*Get the candidate list, if there is only one object in it set the bool to false to break the loop*/

}
void SudokuPuzzle::Solve(char filenameIn[])
{
	InitialiseGrid();
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	SolvePuzzle();
	Output();
	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	cout << "Time Taken: " << time << endl;
	cout << "Loops: " << m_loops << " \nPossible Candidates: " << m_candidateValueConsidered << " \nNumber of Answered Cells: " << m_answered << endl;
}


void SudokuPuzzle::RowCandidates()const
{
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			Cell *rowCell = m_gridRows[row].getRowCell(column);
			vector <int> nonRowCandidates = rowCell->getNonCandidateListNumbers();
			if (rowCell->getValue() != 0)
			{
				rowCell->setDefined(true);
			}
			else
			{
				rowCell->setDefined(false);
			}
			if (rowCell->getDefined() != true)
			{
				for (int checkRow = 0; checkRow < 9; checkRow++)
				{
					Cell *rowCheck = m_gridRows[row].getRowCell(checkRow);
					if (rowCheck->getValue() > 0)
					{
						int nonCandidate = rowCheck->getValue();
						if (find(nonRowCandidates.begin(), nonRowCandidates.end(), nonCandidate) == nonRowCandidates.end())
						{
							rowCell->nonCandidateNumbersAdd(nonCandidate);
						}
					}
				}
			}
		}
	}
}


void SudokuPuzzle::ColumnCandidates()const
{
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			Cell *columnCell = m_gridRows[row].getRowCell(column);
			vector <int> nonColumnCandidates = columnCell->getNonCandidateListNumbers();
			if (columnCell->getValue() != 0)
			{
				columnCell->setDefined(true);
			}
			else
			{
				columnCell->setDefined(false);
			}
			if (columnCell->getDefined() != true)
			{
				for (int checkColumn = 0; checkColumn < 9; ++checkColumn)
				{
					Cell *columnCheck = m_gridColumns[column].getRowCell(checkColumn);
					if (columnCheck->getValue() > 0)
					{
						int nonCandidate = columnCheck->getValue();
						if (find(nonColumnCandidates.begin(), nonColumnCandidates.end(), nonCandidate) == nonColumnCandidates.end())
						{
							columnCell->nonCandidateNumbersAdd(nonCandidate);
						}
					}
				}
			}
		}
	}
}

void SudokuPuzzle::BlockCandidates()const
{
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			Cell* blockCell = m_gridBlocks[row].getRowCell(column);
			vector <int> nonBlockCandidates = blockCell->getNonCandidateListNumbers();
			if (blockCell->getValue() != 0)
			{
				blockCell->setDefined(true);
			}
			else
			{
				blockCell->setDefined(false);
			}
			if (blockCell->getDefined() != true)
			{
				for (int checkBlock = 0; checkBlock < 9; checkBlock++)
				{
					Cell* blockCheck = m_gridBlocks[row].getRowCell(checkBlock);
					if (blockCheck->getValue() > 0)
					{
						int nonCandidate = blockCheck->getValue();
						if (find(nonBlockCandidates.begin(), nonBlockCandidates.end(), nonCandidate) == nonBlockCandidates.end())
						{
							blockCell->nonCandidateNumbersAdd(nonCandidate);
						}
					}
				}
			}
		}
	}
}

void SudokuPuzzle::CandidateList()
{
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			Cell *rowCell = m_gridRows[row].getRowCell(column);
			vector<int>nonCandidateList = rowCell->getNonCandidateListNumbers();
			vector<int>candidateList = rowCell->getCandidateList();
			if (rowCell->getDefined() != true)
			{
				for (int i = 1; i <= 9; ++i)
				{
					if (find(nonCandidateList.begin(), nonCandidateList.end(), i) != nonCandidateList.end())
					{
						rowCell->canidatePointerRemove(i);

					}
					else
					{
						m_candidateValueConsidered++;
					}

				}
			}
		}
	}
}


void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE

	if (fout.is_open())
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				fout << m_gridRows[row].getValue(column) << " ";
				if (column == 8)
				{
					fout << endl;
				}
			}
		}
	}
	fout.close();
}