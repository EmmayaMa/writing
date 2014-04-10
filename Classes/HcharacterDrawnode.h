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
	//�ڵ㿪ʼ���봥��  
	virtual void onEnter();
	//�ڵ��˳�����  
	virtual void onExit();
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


	//************************************
	// Method:    changeStroke 
	// FullName:  HcharacterDrawnode::changeStroke
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: int index �ڼ��ʣ���0��ʼ
	// Parameter: Stroke s ��num���滻�ɴ����stroke
	//************************************
	void changeStroke(int index,Stroke s);

	//************************************
	// Method:    getStroke ��ȡ�ڼ��� ��1��ʼ
	// FullName:  HcharacterDrawnode::getStroke
	// Access:    public 
	// Returns:   Stroke
	// Qualifier:
	// Parameter: int index
	//************************************
	Stroke getStroke(int index);

// 	vector<StrokeDrawnode*> getStrokeDrawnodeList(){ return this->strokeDrawlist; }
// 	vector<StrokeDrawnode*> strokeDrawlist;
	CC_SYNTHESIZE_RETAIN(CCArray*,strokeDrawlist,StrokeDrawnodeList);
private:

};



#endif