#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#pragma once
class Stroke
{
public:
	bool addPoint(CCPoint point);
	float strokeLength();				//һ�ʵĳ���
	void resample();
private:
	float distance(CCPoint p1,CCPoint p2);		//��������
	int strokeBox();					//��¼һ�ʰ�Χ�У��ز���ʹ��
public:
    Stroke(void);
    ~Stroke(void);
    int pointCount;
	CCPoint prePoint;		//����ÿһ���׵�
    vector<CCPoint> pointList;
	vector<CCDrawNode*> nodeList;
};