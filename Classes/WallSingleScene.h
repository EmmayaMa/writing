#ifndef __WallSingleScene_H__
#define __WallSingleScene_H__

#include "cocos2d.h"
#include "HanziManage.h"
#include "PopLayer.h"
#include "tinyxml.h" 
#include "PopLayer.h"
#include "tools/DataTool.h"
#include "LianxiScene.h"
#include "MainScene.h"
#include "MyToast.h"
#include "JudgeScene.h"
#include "SQLiteData.h"
#include <vector>
using namespace std;
USING_NS_CC;

class WallSingleLayer : public CCLayerColor
{
public:
	WallSingleLayer(string unitID);
	~WallSingleLayer();
	vector<CHanziManage> hanzilist;
	string selectedHanzi;
	float rescale;

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void keyBackClicked();

	/**
	 * unitID����
	 * @param unitID
	 * @return
	 */
	static cocos2d::CCScene* scene(string unitID);

	/**
	* unitId and unitidx to create 
	* @param unitID
	* @param unitidx unitidx 0,1,2
	* @return
	*/
	static cocos2d::CCScene* scene(string unitID,int unitidx);

	/**
	 * ��UnitID����
	 * @param unitID
	 * @return
	 */
	static WallSingleLayer* create(string unitID);

	/**
	* ʹ��unitID �Լ� unitIdx ��ͬ������ʶ��ǰ��Ԫ
	* @param unitID
	* @param unitIdx ��ǰ��Ԫ ��0��ʼ 1��2��3.
	* @return
	*/
	static WallSingleLayer* create(string unitID,int unitIdx);

	void menuCloseCallback(CCObject* pSender);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

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

	//��ȡ��ǰʱ�� ��ȷ��������
	static inline long millisecondNow()
	{
		struct cc_timeval now;
		CCTime::gettimeofdayCocos2d(&now, NULL);
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	}

	bool isInSprite(CCTouch* pTouch);
	void singleClick(string hanzi);

	/**
	* �޸�xml�ļ��к��ֶ�Ӧproficiencyֵ
	* @param character Ҫ�޸�profֵ��Ӧ����
	* @param proficiencyҪ�޸ĵ���ֵ
	* @return
	*/
	bool setProficiency(string character,string proficiency);

	/**
	* set the unitidx
	* @param unitidx
	* @return
	*/
	void setUnitIdx(int unitidx);
	
private:
	void backtoMainScene(CCNode* pNode);
	void back(CCObject* pSender);
	PopLayer* popL;
	vector<CHanziManage>::iterator selectedCHanziManageIter;

	CCPoint touchbeginpoint;
	CCPoint prePoint;
	CCPoint changepoint;
	bool touched;
	bool isMoved;
	long beginTime;

	/**
	* ������д
	* @param pSender
	* @return
	*/
	void pingpanwriting(CCObject* pSender);

	/**
	* ������ϰ��Ϣ��Ӧ
	* @param pSender
	* @return
	*/
	void freewriting(CCObject* pSender);

	/**
	* ScreenShot callback
	* @param pSender
	* @return
	*/
	void screenshot(CCObject* pSender);

	vector<string> hanzis;			//ǽ�ϵĺ���
	bool isLongPressAllow;			//�Ƿ�����������
	string unitID;				//��������ͬ��Ԫ�������ݿ��е�ԪID�ж�Ӧ
	int unitIdx;				//����ʶ��ǰ��ԪID  0 1 2 3
	vector<vector <string> > groupCharacter;		//�����ݿ��л�ȡһ����Ԫ�ĺ�������
};

#endif // __WallSingleScene_H__
