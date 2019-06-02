#include "StudentManager.h"
#include "Student.h"

CStudentManager* CStudentManager::m_pInst = nullptr;

CStudentManager::CStudentManager()
{
}


CStudentManager::~CStudentManager()
{
	// 프로그램 종료시 동적할당한 학생 객체 삭제

	CLinkedList<CStudent*>::iterator iter;
	CLinkedList<CStudent*>::iterator iterEnd = m_StudentList.end();

	for (iter = m_StudentList.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_StudentList.clear();
}

bool CStudentManager::Init()
{
	return true;
}

void CStudentManager::Run()
{
	while (1)
	{
		switch (OutputMenu())
		{
		case MM_INSERT:
			Insert();
			break;

		case MM_DELETE:
			Delete();
			break;

		case MM_MODIFY:
			Modify();
			break;

		case MM_OUTPUT:
			Output();
			break;

		case MM_SORT:
			Sort();
			break;

		case MM_QUIT:
			return;
		}
	}
}

MAIN_MENU CStudentManager::OutputMenu()
{
	system("cls");
	cout << MM_INSERT << ". 학생 추가" << endl;
	cout << MM_DELETE << ". 학생 삭제" << endl;
	cout << MM_MODIFY << ". 학생 수정" << endl;
	cout << MM_OUTPUT << ". 학생 출력" << endl;
	cout << MM_SORT << ". 정렬" << endl;
	cout << MM_QUIT << ". 종료" << endl;

	int iMenu;

	cin >> iMenu;

	if (iMenu <= MM_NONE || iMenu > MM_QUIT)
		return MM_NONE;

	else
		return (MAIN_MENU)iMenu;

}

void CStudentManager::Insert()
{
	system("cls");

	cout << " ====================== 학생 추가 ======================" << endl;

	CStudent* pStudent = new CStudent;

	pStudent->SetInfo();

	m_StudentList.push_back(pStudent);

	cout << pStudent->GetName() << "학생이 추가되었습니다." << endl;

	system("pause");
}

void CStudentManager::Delete()
{
	system("cls");

	cout << " ====================== 학생 삭제 ======================" << endl;

	cout << "1. 이름으로 삭제" << endl;
	cout << "2. 학번으로 삭제" << endl;

	int iMenu;
	cin >> iMenu;

	if (iMenu <= 0 || iMenu > 2)
		return;

	CStudent* pStudent = nullptr;

	switch (iMenu)
	{
		case 1: // 이름
		{
			char strName[NAME_SIZE] = {};

			cin >> strName;

			pStudent = FindStudent(strName);
		}
			break;

		case 2: // 학번
		{
			int iInput;
		
			cin >> iInput;

			pStudent = FindStudent(iInput);
		}
			break;

	}

	if (!pStudent)
	{
		cout << "찾는 학생이 없습니다. " << endl;
	}
	else
	{

		CLinkedList<CStudent*>::iterator iter;
		CLinkedList<CStudent*>::iterator iterEnd = m_StudentList.end();

		for (iter = m_StudentList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pStudent)
			{
				SAFE_DELETE(*iter);
				m_StudentList.erase(iter);
				break;
			}
		}
		cout << "학생 삭제 완료" << endl;
		
	}

	system("pause");
}

void CStudentManager::Output()
{

	system("cls");

	cout << " ====================== 학생 출력 ======================" << endl;

	CLinkedList<CStudent*>::iterator iter;
	CLinkedList<CStudent*>::iterator iterEnd = m_StudentList.end();

	for (iter = m_StudentList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Output();
	}

	cout << "학생수 : " << m_StudentList.size() << endl;

	system("pause");
}

void CStudentManager::Sort()
{
	system("cls");

	cout << " ====================== 학생 정렬 ======================" << endl;

	cout << "1. 평균 (오름차순)" << endl;
	cout << "2. 평균 (내림차순)" << endl;

	int iMenu;
	cin >> iMenu;

	if (iMenu <= 0 || iMenu > 2)
		return;


	switch (iMenu)
	{
		case 1: // 오름차순
		{
			m_StudentList.sort(Ascending); // 전역함수를 사용.
		}
		break;

		case 2: // 내림차순
		{
			m_StudentList.sort(Descending);
		}
		break;

	}

	cout << "정렬이 완료되었습니다." << endl;

	system("pause");
}

void CStudentManager::Modify()
{

	system("cls");

	cout << " ====================== 학생 수정 ======================" << endl;

	cout << "1. 이름으로 찾기" << endl;
	cout << "2. 학번으로 찾기" << endl;

	int iMenu;

	cin >> iMenu;

	if (iMenu <= 0 || iMenu > 2)
		return;

	CStudent* pStudent = nullptr;

	switch (iMenu)
	{
	case 1: // 이름
	{
		char strName[NAME_SIZE] = {};

		cin >> strName;

		pStudent = FindStudent(strName);
	}
	break;

	case 2: // 학번
	{
		int iInput;

		cin >> iInput;

		pStudent = FindStudent(iInput);
	}
	break;

	}

	if (!pStudent)
	{
		cout << "찾는 학생이 없습니다. " << endl;
	}
	else
	{

		CLinkedList<CStudent*>::iterator iter;
		CLinkedList<CStudent*>::iterator iterEnd = m_StudentList.end();

		for (iter = m_StudentList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pStudent)
			{
				(*iter)->SetInfo();
				break;
			}
		}

		cout << "학생 수정 완료" << endl;
	}

	system("pause");
}

CStudent * CStudentManager::FindStudent(int iNumber)
{
	CLinkedList<CStudent*>::iterator iter;
	CLinkedList<CStudent*>::iterator iterEnd = m_StudentList.end();

	for (iter = m_StudentList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetNumber() == iNumber)
			return *iter;
	}

	return nullptr;
}

CStudent * CStudentManager::FindStudent(const char * strName)
{
	CLinkedList<CStudent*>::iterator iter;
	CLinkedList<CStudent*>::iterator iterEnd = m_StudentList.end();

	for (iter = m_StudentList.begin(); iter != iterEnd; ++iter)
	{
		if (strcmp(strName, (*iter)->GetName()) == 0)
			return *iter;
	}

	return nullptr;
}

bool CStudentManager::Ascending(CStudent * const & s1, CStudent * const & s2)
{
	return s1->GetTotal() > s2->GetTotal();
}

bool CStudentManager::Descending(CStudent * const & s1, CStudent * const & s2)
{
	return s1->GetTotal() < s2->GetTotal();
}
