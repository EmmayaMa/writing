#ifndef __Stroke_H__
#define __Stroke_H__

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
	CCSize getRotateAng();						//��ȡβ�㵽�׵������
	CCPoint getMidPoint();						//��ȡһ���е㣬�����Ϊ�׵��β����е�
	CCSize getSize();
	CCPoint getBigPoint();						//��ȡ����ֵ���ĵ㣬��Χ�������Ͻǵĵ�
// 	StrokeNode* getStrokeNode();
private:
	float distance(CCPoint p1,CCPoint p2);		//��������
	int getStrokeBox();					//��¼һ�ʰ�Χ�У��ز���ʹ��
public:
    Stroke(void);
    ~Stroke(void);
    int pointCount;
	CCPoint prePoint;		//����ÿһ���׵�
    vector<CCPoint> pointList;
	vector<CCDrawNode*> nodeList;
};

#endif