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
	/**
	* ����TcharacterLayer��HcharacterLayer��ʼ��TouchLayer
	* @param t
	* @param h
	* @return
	*/
	virtual bool init(TcharacterLayer* t,HcharacterLayer* h);
	virtual void onEnter();
	virtual void onExit();
	/**
	* ����TcharacterLayer��HcharacterLayer����TouchLayer
	* @param t
	* @param h
	* @return
	*/
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
	CCPoint beginPoint;			//������д�ĵ�һ����
	bool isOutside;
	bool isStartOutside;
};



#endif // !__TouchLayer_H__
