
#include "StudentManager.h"

int main()
{
	if (!CStudentManager::GetInst()->Init())
	{
		CStudentManager::DestroyInst();

		return 0;
	}

	CStudentManager::GetInst()->Run();

	CStudentManager::GetInst()->DestroyInst();

	return 0;
}