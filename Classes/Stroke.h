#ifndef __Stroke_H__
#define __Stroke_H__

#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Stroke
{
public:
	Stroke(void);
	/**
	* create a stroke with a group of points
	* @param points
	* @return
	*/
	Stroke(vector<CCPoint> points);
	~Stroke(void);
	int pointCount;
	CCPoint prePoint;		//����ÿһ���׵�
	vector<CCPoint> pointList;
	vector<CCDrawNode*> nodeList;
public:
	/**
	* add a point to stroke
	* @param point
	* @return
	*/
	bool addPoint(CCPoint point);

	/**
	* length of a stroke:sum of each distance between two points
	* @return
	*/
	float strokeLength();

	/**
	* �ز�������ֵ���� x�᷽��ÿ10pxһ��
	* @param n Ĭ��Ϊ20�����������趨
	* @return
	*/
	void resample(int n = 20);

	CCSize getRotateAng();						//��ȡβ�㵽�׵������
	CCPoint getMidPoint();						//��ȡһ���е㣬�����Ϊ�׵��β����е�
	CCSize getSize();
	CCPoint getBigPoint();						//��ȡ����ֵ���ĵ㣬��Χ�������Ͻǵĵ�
	string sendOutput();						//�����͸�Lua���ַ���

	/**
	* ��pointList��ÿ��point����һ��pointֵ
	* @param point
	* @return
	*/
	void addEveryPoint(CCPoint point);			//ÿ�����һ����
// 	StrokeNode* getStrokeNode();
private:
	float distance(CCPoint p1,CCPoint p2);		//��������
	int getStrokeBox();					//��¼һ�ʰ�Χ�У��ز���ʹ��
	string convertToString(float f);
};

#endif