#include "CellGroup.h"
#include "Cell.h"
using namespace std;
#include <iostream>


CellGroup::CellGroup() : rowCells()
{
}

CellGroup::~CellGroup()
{
}

void CellGroup::setCell(int index, Cell* cell)
{
	rowCells[index] = cell;
}

Cell* CellGroup::getRowCell(int row)const
{
	return rowCells[row];
}

int CellGroup::getValue(int value)const
{
	return rowCells[value]->getValue();
}