#ifndef __StrokeDrawnode_H__
#define __StrokeDrawnode_H__

#include "cocos2d.h"
#include "Stroke.h"
USING_NS_CC;
using namespace std;

/************************************************************************/
/* ÿһ���ʻ��Ļ����࣬�̳���CCNode                                                                     */
/************************************************************************/
class StrokeDrawnode : public CCNode
{
public:
	StrokeDrawnode();
	/**
	* ��Stroke����һ��Node
	* @param stro
	* @return
	*/
	StrokeDrawnode(Stroke stro);
	~StrokeDrawnode();
	/**
	* create a StrokeDrawnode
	* @param stro
	* @return
	*/
	static StrokeDrawnode* create(Stroke stro);
	//�ڵ㿪ʼ���봥��
	virtual void onEnter();
	//�ڵ��˳�����
	virtual void onExit();
	virtual void draw();

	/**
	* add a point to stroke
	* @param point
	* @return
	*/
	void addPoint(CCPoint point);
	/**
	* return Stroke
	* @return
	*/
	Stroke getStroke(){return stroke;}
private:
	Stroke stroke;					//store points in a stroke
	ccColor4B mcolor;				//color if this stroke:have not used yet
	int visibleIndex;				

};


#endif