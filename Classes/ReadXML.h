#include "Character.h"

using namespace std;
#pragma once
/************************************************************************/
/* ��ȡ������ÿһ�����֣��ʻ�xml                                                                     */
/************************************************************************/
class CReadXML
{
public:
	Character* getCharacter();
public:
	CReadXML(void);
	CReadXML(string xmlpath);
	~CReadXML(void);
	Character character;
};

