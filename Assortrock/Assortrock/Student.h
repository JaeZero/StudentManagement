#pragma once
#include "Management.h"

class CStudent
{
public:
	CStudent();
	~CStudent();

private:
	char	m_strName[NAME_SIZE];
	int		m_iNumber;
	int		m_iKor;
	int		m_iEng;
	int		m_iMath;
	int		m_iTotal;
	float	m_fAvg;
	char	m_cGrade;

public:
	void SetName(const char* strName);
	void SetNumber(int iNumber);
	void SetKor(int iKor);
	void SetEng(int iEng);
	void SetMath(int iMath);
	void SetScore(int iKor, int iEng, int iMath);

	void Output();

	void SetInfo();

	char* GetName();
	int GetNumber() const;
	int GetTotal() const;
};

