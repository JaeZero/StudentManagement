#pragma once

#include "Management.h"

class CStudentManager
{
private:
	CStudentManager();
	~CStudentManager();

private:
	static CStudentManager*		m_pInst;

	CLinkedList<class CStudent*>	m_StudentList;
	

public:
	static	CStudentManager*	GetInst()
	{
		if (!m_pInst)
			m_pInst = new CStudentManager;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

public:
	bool Init();
	void Run();


private:
	MAIN_MENU OutputMenu();

	void Insert();
	void Delete();
	void Output();
	void Sort();
	void Modify();

	class CStudent* FindStudent(int iNumber);
	class CStudent* FindStudent(const char* strName);

	static bool Ascending(class CStudent* const &s1, class CStudent* const &s2);
	static bool Descending(class CStudent* const &s1, class CStudent* const &s2);
	
};

