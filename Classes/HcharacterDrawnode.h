#ifndef _HcharacterDrawnode_H__
#define _HcharacterDrawnode_H__

#include "cocos2d.h"
#include "StrokeDrawnode.h"
#include "Stroke.h"
USING_NS_CC;

class HcharacterDrawnode : public CCNode
{
public:
	HcharacterDrawnode();
	~HcharacterDrawnode();
	CREATE_FUNC(HcharacterDrawnode);
	virtual bool init();
	virtual void draw();

	//************************************
	// Method:    addPoint �����һ�������ӵ�
	// FullName:  HcharacterDrawnode::addPoint
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: CCPoint point
	//************************************
	void addPoint(CCPoint point);

	//************************************
	// Method:    addStroke ���һ��
	// FullName:  HcharacterDrawnode::addStroke
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: Stroke s
	//************************************
	void addStroke(Stroke s);

	//************************************
	// Method:    removeLastStroke ɾ�����һ��
	// FullName:  HcharacterDrawnode::removeLastStroke
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void removeLastStroke();

// 	vector<StrokeDrawnode*> getStrokeDrawnodeList(){ return this->strokeDrawlist; }
// 	vector<StrokeDrawnode*> strokeDrawlist;
	CC_SYNTHESIZE_RETAIN(CCArray*,strokeDrawlist,StrokeDrawnodeList);
private:

};



#endif