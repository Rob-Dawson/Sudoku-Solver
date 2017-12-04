#include "Cell.h"


Cell::Cell() : m_value(), m_define()
{
}

Cell::Cell(int cellValue): m_define()
{
	setValue(cellValue);
}

Cell::~Cell()
{
}



int Cell::getValue(void)const
{
	return m_value;
}

void Cell::setValue(int cellValue)
{
	m_value = cellValue;
}

bool Cell::getDefined()const
{
	if (m_define == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cell::setDefined(bool cellValue)
{
	m_define = cellValue;
}

void Cell::setCandidateList(vector<int> candidateList)
{
	m_candidateList = candidateList;
}



void Cell::nonCandidateNumbersAdd(int cellValue)
{
	m_nonCandidateListNumbers.push_back(cellValue);
}