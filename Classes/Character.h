#include "Bujian.h"
#include <vector>

#pragma once

using namespace std;
USING_NS_CC;

class Character
{
public:
	bool addBujian(Bujian bujian);
	//************************************
	// Method:    getBox ��ȡ��Χ��
	// FullName:  Character::getBox
	// Access:    public 
	// Returns:   cocos2d::CCSize
	// Qualifier:
	//************************************
	CCSize getBox();
	//************************************
	// Method:    getStrokeCount ��ȡ�ֵıʻ���
	// FullName:  Character::getStrokeCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	//************************************
	int getStrokeCount();
	void resize(CCSize size);
	void resample();
	void prepareDrawNode();
	//************************************
	// Method:    getStroke ��ȡ��no�ʣ��ʻ���1��ʼ
	// FullName:  Character::getStroke
	// Access:    public 
	// Returns:   Stroke
	// Qualifier:
	// Parameter: int no
	//************************************
	Stroke getStroke(int no);
public:
	Character(void);
	~Character(void);
	int bujianCount;
	int fontSize;		//���ִ�С��Ĭ��512
	vector<Bujian> bujianList;
private:
	void transformCoordinate(CCPoint point,float length);

};

