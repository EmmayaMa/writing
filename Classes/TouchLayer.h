#ifndef __TouchLayer_H__
#define __TouchLayer_H__

#include "cocos2d.h"
#include "TcharacterLayer.h"
#include "HcharacterLayer.h"
USING_NS_CC;
using namespace std;

class TouchLayer : public CCLayerColor
{
public:
	TouchLayer();
	~TouchLayer();
	virtual bool init(TcharacterLayer* t,HcharacterLayer* h);
	virtual void onEnter();
	virtual void onExit();
// 	CREATE_FUNC(TouchLayer);
	static TouchLayer* create(TcharacterLayer* t,HcharacterLayer* h);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

	CC_SYNTHESIZE_RETAIN(TcharacterLayer* ,Tlayer,Tlayer);
	CC_SYNTHESIZE_RETAIN(HcharacterLayer* ,Hlayer,Hlayer);
private:
	int index;				//���浱ǰ��д�ĵڼ���
	int errorType;			//��ǰ��д�ʻ���������
	vector<CCPoint> points;		//������д��
	bool isOutside;
	bool isStartOutside;
};



#endif // !__TouchLayer_H__
