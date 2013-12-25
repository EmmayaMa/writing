#ifndef __LIANXI_H__
#define __LIANXI_H__

#include "cocos2d.h"
#include "Character.h"
USING_NS_CC;
using namespace std;

class lianxi : public CCLayer{

public:
    lianxi();
    ~lianxi();
    virtual bool init();
	virtual void onExit();
	virtual void onEnter();
//    virtual void draw();
    static CCScene* scene(string hanzi);
    CREATE_FUNC(lianxi);
    
//     bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//     void  ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//     void  ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

    void keyBackClicked();
	void clearStroke(float fDelta);		//д��һ��֮��1s��Ӧ����
private:
	Character charac;
	Character character;			//store writing character not used yet
	vector<CCDrawNode*> writing_stroke;
    string hanzi;
    CCPoint prePoint;				//store first writing point
	CCPoint centerPoint;			//������д�֣����ĵ���Ϣ
    void menuBack(CCObject* pSender);
	string convertToString(float f);
	string output;

	void DoAnimation();
	CCPoint centerP(CCPoint p1,CCPoint p2);		//�����е�����
};

#endif