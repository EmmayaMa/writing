#ifndef __TouchLayer_H__
#define __TouchLayer_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class TouchLayer : public CCLayerColor
{
public:
	TouchLayer();
	~TouchLayer();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(TouchLayer);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

private:
	int index;				//���浱ǰ��д�ĵڼ���
	int errorType;			//��ǰ��д�ʻ���������

};



#endif // !__TouchLayer_H__
