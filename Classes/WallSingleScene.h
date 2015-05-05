#ifndef __WallSingleScene_H__
#define __WallSingleScene_H__

#include "cocos2d.h"
#include "HanziManage.h"
#include "PopLayer.h"
#include <vector>
using namespace std;
USING_NS_CC;

class WallSingleScene : public CCLayer
{
public:
	WallSingleScene();
	~WallSingleScene();
	vector<CHanziManage> hanzilist;
	string selectedHanzi;
	float rescale;

	virtual bool init(string xmlfilename);
	virtual void onEnter();
	virtual void onExit();
	virtual void keyBackClicked();

	static cocos2d::CCScene* scene(string filename);

	void menuCloseCallback(CCObject* pSender);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

	static WallSingleScene* create(string wallxmlname);

	/**
	* �����Ի���
	* @param hanzi
	* @return
	*/
	void popup(string hanzi);
	
	/**
	* �Ի���ص�����
	* @param pNode
	* @return
	*/
	void buttonCallBack(CCNode* pNode);

	virtual void update(float delta);
	//����
	void longPressUpdate(float fDelta);

	//���浽xml�ļ�
	void saveToFile(string src,const char* dst);

	//��ȡ��ǰʱ�� ��ȷ��������
	static inline long millisecondNow()
	{
		struct cc_timeval now;
		CCTime::gettimeofdayCocos2d(&now, NULL);
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	}

	bool isInSprite(CCTouch* pTouch);
	void singleClick(string hanzi);
	string getwallXmlName()	{ return wallXMLCurrent; }

	/**
	* �޸�xml�ļ��к��ֶ�Ӧproficiencyֵ
	* @param character Ҫ�޸�profֵ��Ӧ����
	* @param proficiencyҪ�޸ĵ���ֵ
	* @return
	*/
	bool setProficiency(string character,string proficiency);
	
private:
	void backtoMainScene(CCNode* pNode);
	PopLayer* popL;
	vector<CHanziManage>::iterator selectedCHanziManageIter;

	CCPoint touchbeginpoint;
	CCPoint prePoint;
	CCPoint changepoint;
	bool touched;
	bool isMoved;
	long beginTime;

	// xml �ļ���
	string wallXMLCurrent;
	/*
		���԰�ť��Ӧ����
	*/
	void ceshi(CCObject* pSender);

	vector<string> hanzis;
	bool isLongPressAllow;
};

#endif // __WallSingleScene_H__
