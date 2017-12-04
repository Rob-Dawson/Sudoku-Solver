#pragma once
#include "Cell.h"
class CellGroup
{
public:
	CellGroup();
	~CellGroup();

	void setCell(int index, Cell *cell);

	Cell* getRowCell(int index)const;

	int getValue(int value)const;

private:
	Cell* rowCells[9]; // create 9 cell pointers
};

