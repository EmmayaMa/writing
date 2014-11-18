#ifndef __Stroke_H__
#define __Stroke_H__

#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Stroke
{
public:
	friend class StrokeNode;

	Stroke(void);
	/**
	* create a stroke with a group of points
	* @param points
	* @return
	*/
	Stroke(vector<CCPoint> points);
	~Stroke(void);
	vector<CCDrawNode*> nodeList;
	CCPoint prePoint;		//����ÿһ���׵�
public:
	/**
	 * ��ȡ������
	 * @return
	 */
	int getPointsCount();

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

	/**
	* ��pointList��ÿ��point����һ��pointֵ
	* @param point
	* @return
	*/
	void addEveryPoint(CCPoint point);			//ÿ�����һ����
// 	StrokeNode* getStrokeNode();

	/**
	* get the whole pointList
	* @return
	*/
	vector<CCPoint> getpointList();

	CCPoint getpointListIndexAt(int i);

	/**
	* set the point in pointList 
	* @param index	the index of the point want to change
	* @param pointSet	the point you want to change
	* @return
	*/
	void setpointList(int index, CCPoint pointSet);

	/**
	* to construct a list of status of points
	* @param status
	* @return
	*/
	void addStatus(const char* status);

	/**
	* �����͸�Lua���ַ���
	* @return
	*/
	string sendOutput();

	/**
	* �����͸�Lua���ַ���
	* @return
	*/
	string sendOutputWithStatus();

private:
	int pointCount;

	float distance(CCPoint p1,CCPoint p2);		//��������
	int getStrokeBox();					//��¼һ�ʰ�Χ�У��ز���ʹ��
	string convertToString(float f);

	vector<CCPoint> pointList;				//store a group of points
	vector<string> statusList;				//store the status read from XML to judge whether the point is inflected
};

#endif
