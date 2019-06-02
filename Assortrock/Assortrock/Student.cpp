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
	cout << "�̸� : " << m_strName << "\t�й� : " << m_iNumber << endl;
	cout << "���� : " << m_iKor << "\t���� : " << m_iEng << "\t���� : " << m_iMath << endl;
	cout << "���� : " << m_iTotal << "\t��� : " << m_fAvg << "\t��� : " << m_cGrade << endl << endl;
}

void CStudent::SetInfo()
{
	cout << "�̸� : ";
	cin >> m_strName;

	cout << "�й� : ";
	cin >> m_iNumber;

	cout << "���� : ";
	cin >> m_iKor;

	cout << "���� : ";
	cin >> m_iEng;

	cout << "���� : ";
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
