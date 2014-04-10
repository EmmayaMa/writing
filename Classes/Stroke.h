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
	Stroke(vector<CCPoint> points);				//����һ���㣬����һ��
	~Stroke(void);
	int pointCount;
	CCPoint prePoint;		//����ÿһ���׵�
	vector<CCPoint> pointList;
	vector<CCDrawNode*> nodeList;
public:
	bool addPoint(CCPoint point);
	float strokeLength();				//һ�ʵĳ���
	//************************************
	// Method:    resample �ز�������ֵ����
	// FullName:  Stroke::resample
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void resample();
	CCSize getRotateAng();						//��ȡβ�㵽�׵������
	CCPoint getMidPoint();						//��ȡһ���е㣬�����Ϊ�׵��β����е�
	CCSize getSize();
	CCPoint getBigPoint();						//��ȡ����ֵ���ĵ㣬��Χ�������Ͻǵĵ�
	string sendOutput();						//�����͸�Lua���ַ���
	//************************************
	// Method:    addEveryPoint ��pointList��ÿ��point����һ��pointֵ
	// FullName:  Stroke::addEveryPoint
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: CCPoint point
	//************************************
	void addEveryPoint(CCPoint point);			//ÿ�����һ����
// 	StrokeNode* getStrokeNode();
private:
	float distance(CCPoint p1,CCPoint p2);		//��������
	int getStrokeBox();					//��¼һ�ʰ�Χ�У��ز���ʹ��
	string convertToString(float f);
};

#endif