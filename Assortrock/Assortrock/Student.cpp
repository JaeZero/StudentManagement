#include "Student.h"



CStudent::CStudent()
{
	memset(m_strName, 0, NAME_SIZE);
}


CStudent::~CStudent()
{
}

void CStudent::SetName(const char * strName)
{
	strcpy_s(m_strName, strName);
}

void CStudent::SetNumber(int iNumber)
{
	m_iNumber = iNumber;
}

void CStudent::SetKor(int iKor)
{
	m_iKor = iKor;
}

void CStudent::SetEng(int iEng)
{
	m_iEng = iEng;
}

void CStudent::SetMath(int iMath)
{
	m_iMath = iMath;
}

void CStudent::SetScore(int iKor, int iEng, int iMath)
{
	m_iKor = iKor;
	m_iEng = iEng;
	m_iMath = iMath;

	m_iTotal = iKor + iEng + iMath;

	m_fAvg = m_iTotal / 3.f;

	if (m_fAvg >= 90.f)
		m_cGrade = 'A';
	else if (m_fAvg >= 80.f)
		m_cGrade = 'B';
	else if (m_fAvg >= 70.f)
		m_cGrade = 'C';
	else
		m_cGrade = 'F';

}

void CStudent::Output()
{
	cout << "이름 : " << m_strName << "\t학번 : " << m_iNumber << endl;
	cout << "국어 : " << m_iKor << "\t영어 : " << m_iEng << "\t수학 : " << m_iMath << endl;
	cout << "총점 : " << m_iTotal << "\t평균 : " << m_fAvg << "\t등급 : " << m_cGrade << endl << endl;
}

void CStudent::SetInfo()
{
	cout << "이름 : ";
	cin >> m_strName;

	cout << "학번 : ";
	cin >> m_iNumber;

	cout << "국어 : ";
	cin >> m_iKor;

	cout << "영어 : ";
	cin >> m_iEng;

	cout << "수학 : ";
	cin >> m_iMath;

	m_iTotal = m_iKor + m_iEng + m_iMath;

	m_fAvg = m_iTotal / 3.f;

	if (m_fAvg >= 90.f)
		m_cGrade = 'A';
	else if (m_fAvg >= 80.f)
		m_cGrade = 'B';
	else if (m_fAvg >= 70.f)
		m_cGrade = 'C';
	else
		m_cGrade = 'F';
}

char * CStudent::GetName() 
{
	return m_strName;
}

int CStudent::GetNumber() const
{
	return m_iNumber;
}

int CStudent::GetTotal() const
{
	return m_iTotal;
}
