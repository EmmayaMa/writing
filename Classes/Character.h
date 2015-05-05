#include "Bujian.h"
#include <vector>

#pragma once

using namespace std;
USING_NS_CC;

class Character
{
public:
	bool addBujian(Bujian bujian);

	/**
	* getBox ��ȡ��Χ��
	* @return
	*/
	CCSize getBox();

	/**
	* getStrokeCount ��ȡ�ֵıʻ���
	* @return
	*/
	int getStrokeCount();
	void resize(CCSize size);
	void resample();
	void prepareDrawNode();

	/**
	* getStroke ��ȡ��no�ʣ��ʻ���1��ʼ
	* @param no
	* @return
	*/
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

