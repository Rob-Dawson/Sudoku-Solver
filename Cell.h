#pragma once
#include <vector>
#include <algorithm>
using namespace std;
class Cell
{
	//friend class SudokuPuzzle;
public:
	Cell(); //Keep this one
	explicit Cell(int cellValue); //new constructor to handle input
	~Cell();
	int getValue(void)const;
	void setValue(int cellValue);

	bool getDefined() const;
	void setDefined(bool cellValue);

	vector<int> getCandidateList() const { return m_candidateList; }	
	void setCandidateList(vector<int>candidateList);

	vector<int> getNonCandidateListNumbers()const { return m_nonCandidateListNumbers; }
	void nonCandidateNumbersAdd(int cellValue);

	void canidatePointerRemove(int temp)
	{
		if (find(m_candidateList.begin(), m_candidateList.end(), temp) != m_candidateList.end())
		{		
			m_candidateList.erase(remove(m_candidateList.begin(), m_candidateList.end(), temp));
		}

	}
	

private:
	vector<int> m_candidateList{ 1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<int> m_nonCandidateListNumbers;
	//bool m_candidateList[9];
	int m_value;
	bool m_define;
};
