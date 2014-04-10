#ifndef __StrokeDrawnode_H__
#define __StrokeDrawnode_H__

#include "cocos2d.h"
#include "Stroke.h"
USING_NS_CC;
using namespace std;

class StrokeDrawnode : public CCNode
{
public:
	StrokeDrawnode();
	StrokeDrawnode(Stroke stro);
	~StrokeDrawnode();
	static StrokeDrawnode* create(Stroke stro);
	//�ڵ㿪ʼ���봥��  
	virtual void onEnter();
	//�ڵ��˳�����
	virtual void onExit();

	virtual void draw();
	int visibleIndex;
	void addPoint(CCPoint point);
	Stroke getStroke(){return stroke;}
private:
	Stroke stroke;
	ccColor4B mcolor;
};


#endif