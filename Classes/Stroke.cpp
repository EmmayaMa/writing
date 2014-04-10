#include "Stroke.h"

USING_NS_CC;
#include <cmath>

Stroke::Stroke(void)
{
	this->pointCount=0;

}

Stroke::Stroke(vector<CCPoint> points){
	if (points.size() > 0)
	{
		this->pointList = points;
		this->pointCount = points.size();
		this->prePoint = points.at(0);
	}
}


Stroke::~Stroke(void)
{
	pointList.clear();
}

/************************************************************************/
/* ������뵽pointListβ                                                                     */
/************************************************************************/
bool Stroke::addPoint(CCPoint point){
	this->pointCount++;
	if (pointList.empty())
	{
		prePoint = point;
	}
	vector<CCPoint>::iterator it = pointList.end();
	this->pointList.insert(it,point);

	return true;
}

float Stroke::distance(CCPoint p1,CCPoint p2){
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	return sqrt(dx*dx + dy*dy);
}

float Stroke::strokeLength(){
	float length = 0;
	for (int i= 1; i < pointList.size() ; ++i)
	{
		length += distance(pointList.at(i-1),pointList.at(i));
	}
	return length;
}

int Stroke::getStrokeBox(){
	float dx = fabs(pointList.at(0).x-pointList.at(pointList.size()-1).x);
	float dy = fabs(pointList.at(0).y-pointList.at(pointList.size()-1).y);
	return dx>dy?dx:dy;
}

void Stroke::resample(int n){
// 	int n = getStrokeBox()/10;			//��ȡ�����������ֵ
	float I = strokeLength() / (n-1);		//10������һ��
	float D = 0;

	vector<CCPoint> dstpoList;
	dstpoList.push_back(pointList.at(0));

	for (int i = 1; i < pointList.size() ; ++i )
	{
		CCPoint p1 = pointList[i-1];
		CCPoint p2 = pointList[i];

		float dist = distance(p1,p2);
		if ( (D+dist) >= I)
		{
			float qx = p1.x + ((I - D) / dist) * (p2.x - p1.x);
			float qy = p1.y + ((I - D) / dist) * (p2.y - p1.y);
			vector<CCPoint>::iterator it = pointList.begin();
			pointList.insert(it+i,CCPointMake(qx,qy));
			dstpoList.push_back(CCPointMake(qx,qy));
			D = 0.0;
		}
		else
		{
			D += dist;
		}
	}
	if (dstpoList.size() == n-1)
	{
		dstpoList.insert(dstpoList.end(),pointList.at(pointList.size()-1));
	}
	pointList = dstpoList;
	pointCount = pointList.size();
	prePoint = pointList[0];
}

CCSize Stroke::getRotateAng(){
	CCPoint lastPoint = pointList[pointList.size()-1];
	float width = prePoint.x - lastPoint.x;
	float height = prePoint.y - lastPoint.y;
	return CCSizeMake(width,height);
}

CCPoint Stroke::getMidPoint(){
	return ccpMidpoint(pointList[0],pointList[pointList.size()-1]);
}

CCSize Stroke::getSize(){
	return CCSizeMake(getStrokeBox(),getStrokeBox());
}
CCPoint Stroke::getBigPoint(){
	float tx=0,ty=0;
	for (vector<CCPoint>::const_iterator it = pointList.begin(); it != pointList.end(); ++it)
	{
		CCPoint tmp = (*it);
		if (tmp.x > tx)
		{
			tx = tmp.x;
		}
		if (tmp.y > ty)
		{
			ty = tmp.y;
		}
	}
	return ccp(tx,ty);
}

void Stroke::addEveryPoint(CCPoint point){
	for (int i = 0 ; i < pointList.size(); ++i)
	{
		pointList[i] = pointList[i] + point;
	}
}

// StrokeNode* Stroke::getStrokeNode(){
// 	return 
/*}*/

string Stroke::sendOutput(){
	string ret;
	for (vector<CCPoint>::const_iterator it = pointList.begin(); it != pointList.end() ; ++it)
	{
		CCPoint temp = (*it);
		ret += convertToString(ceil(temp.x))+ "/" + convertToString(ceil(temp.y)) + "/";
	}
	ret += "@";
	return ret;
}

string Stroke::convertToString(float f){
	ostringstream buff;
	buff<<f;
	return buff.str();
}