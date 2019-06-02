#pragma once

#include <iostream>

using namespace std;


#include "CLinkedList.h"

#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p = nullptr;}
#define NAME_SIZE	32

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_MODIFY,
	MM_OUTPUT,
	MM_SORT,
	MM_QUIT
};
