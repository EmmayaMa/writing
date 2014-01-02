#ifndef __LIANXI_H__
#define __LIANXI_H__

#include "cocos2d.h"
#include "Character.h"
#include "StrokeNode.h"
#include "LuaScriptReader.h"

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
	Character newCharac;
	Character Originccccc;
	CCNode* writing_points_node;
	vector<CCDrawNode*> writing_stroke;
	vector<CCPoint> writing_points;			//����д�������ֵ㼯��Ϣ
    string hanzi;
    CCPoint writing_prePoint;				//store first writing point ��������ʱ�仯
	CCPoint centerPoint;			//������д�֣����ĵ���Ϣ
    void menuBack(CCObject* pSender);
	string convertToString(float f);
	CCPoint convert512(CCPoint p);					//������ת����512��Χ��
	string output;
	CCSprite* tianzige;
	CCSprite* tianzige_draw;
	void DoAnimation();

	StrokeNode* my_strokenode;
	vector<StrokeNode*> strokeNodes;
	int current_writing_stroke;				//��ǰд�ڼ��� 1,2,3,4....
};

#endif