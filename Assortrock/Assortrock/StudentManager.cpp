#include "StudentManager.h"
#include "Student.h"

CStudentManager* CStudentManager::m_pInst = nullptr;

CStudentManager::CStudentManager()
{
}


CStudentManager::~CStudentManager()
{
	// ���α׷� ����� �����Ҵ��� �л� ��ü ����

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
	cout << MM_INSERT << ". �л� �߰�" << endl;
	cout << MM_DELETE << ". �л� ����" << endl;
	cout << MM_MODIFY << ". �л� ����" << endl;
	cout << MM_OUTPUT << ". �л� ���" << endl;
	cout << MM_SORT << ". ����" << endl;
	cout << MM_QUIT << ". ����" << endl;

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

	cout << " ====================== �л� �߰� ======================" << endl;

	CStudent* pStudent = new CStudent;

	pStudent->SetInfo();

	m_StudentList.push_back(pStudent);

	cout << pStudent->GetName() << "�л��� �߰��Ǿ����ϴ�." << endl;

	system("pause");
}

void CStudentManager::Delete()
{
	system("cls");

	cout << " ====================== �л� ���� ======================" << endl;

	cout << "1. �̸����� ����" << endl;
	cout << "2. �й����� ����" << endl;

	int iMenu;
	cin >> iMenu;

	if (iMenu <= 0 || iMenu > 2)
		return;

	CStudent* pStudent = nullptr;

	switch (iMenu)
	{
		case 1: // �̸�
		{
			char strName[NAME_SIZE] = {};

			cin >> strName;

			pStudent = FindStudent(strName);
		}
			break;

		case 2: // �й�
		{
			int iInput;
		
			cin >> iInput;

			pStudent = FindStudent(iInput);
		}
			break;

	}

	if (!pStudent)
	{
		cout << "ã�� �л��� �����ϴ�. " << endl;
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
		cout << "�л� ���� �Ϸ�" << endl;
		
	}

	system("pause");
}

void CStudentManager::Output()
{

	system("cls");

	cout << " ====================== �л� ��� ======================" << endl;

	CLinkedList<CStudent*>::iterator iter;
	CLinkedList<CStudent*>::iterator iterEnd = m_StudentList.end();

	for (iter = m_StudentList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Output();
	}

	cout << "�л��� : " << m_StudentList.size() << endl;

	system("pause");
}

void CStudentManager::Sort()
{
	system("cls");

	cout << " ====================== �л� ���� ======================" << endl;

	cout << "1. ��� (��������)" << endl;
	cout << "2. ��� (��������)" << endl;

	int iMenu;
	cin >> iMenu;

	if (iMenu <= 0 || iMenu > 2)
		return;


	switch (iMenu)
	{
		case 1: // ��������
		{
			m_StudentList.sort(Ascending); // �����Լ��� ���.
		}
		break;

		case 2: // ��������
		{
			m_StudentList.sort(Descending);
		}
		break;

	}

	cout << "������ �Ϸ�Ǿ����ϴ�." << endl;

	system("pause");
}

void CStudentManager::Modify()
{

	system("cls");

	cout << " ====================== �л� ���� ======================" << endl;

	cout << "1. �̸����� ã��" << endl;
	cout << "2. �й����� ã��" << endl;

	int iMenu;

	cin >> iMenu;

	if (iMenu <= 0 || iMenu > 2)
		return;

	CStudent* pStudent = nullptr;

	switch (iMenu)
	{
	case 1: // �̸�
	{
		char strName[NAME_SIZE] = {};

		cin >> strName;

		pStudent = FindStudent(strName);
	}
	break;

	case 2: // �й�
	{
		int iInput;

		cin >> iInput;

		pStudent = FindStudent(iInput);
	}
	break;

	}

	if (!pStudent)
	{
		cout << "ã�� �л��� �����ϴ�. " << endl;
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

		cout << "�л� ���� �Ϸ�" << endl;
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
