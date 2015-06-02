#ifndef __NewUnit_H__
#define __NewUnit_H__

#include "cocos2d.h"
#include "cocos-ext.h"
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
USING_NS_CC_EXT;

class NewUnitLayer : public CCLayerColor, CCEditBoxDelegate
{
public:
	NewUnitLayer(string unitID);
	~NewUnitLayer();
	vector<CHanziManage> hanzilist;
	string selectedHanzi;
	float rescale;

	/**
	* ����add ������һ����Ԫ���������>=0��ֵ��Ϊ�޸ĸ�ID�ĵ�Ԫ
	* @param unitID add ���� >=0 ������ID ��ԪID
	* @return
	*/
	static cocos2d::CCScene* scene(string unitID);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void keyBackClicked();

	void menuCloseCallback(CCObject* pSender);

// 	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

	static NewUnitLayer* create(string unitID);

	//��ʼ�༭ʱ
	virtual void editBoxEditingDidBegin(CCEditBox* editBox);
	//�����༭ʱ
	virtual void editBoxEditingDidEnd(CCEditBox* editBox);
	//�༭�����ָı�ʱ
	virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
	//����return��
	virtual void editBoxReturn(CCEditBox* editBox);
	
	/**
	* �޸�xml�ļ��к��ֶ�Ӧproficiencyֵ
	* @param character Ҫ�޸�profֵ��Ӧ����
	* @param proficiencyҪ�޸ĵ���ֵ
	* @return
	*/
	bool setProficiency(string character,string proficiency);
	
	CC_SYNTHESIZE_RETAIN(CCEditBox*, m_editBox, m_editBox);

private:
// 	void backtoMainScene(CCNode* pNode);
	void back(CCObject* pSender);
	void finishAddUnit(CCObject* pSender);
	void deleteUnit(CCObject* pSender);
	void updateUnit(CCObject* pSender);
	PopLayer* popL;
	vector<CHanziManage>::iterator selectedCHanziManageIter;

	vector<string> hanzis;			//ǽ�ϵĺ���
	string unitID;				//��������ͬ��Ԫ�������ݿ��е�ԪID�ж�Ӧ
	vector<vector <string> > groupCharacter;		//�����ݿ��л�ȡһ����Ԫ�ĺ�������
	int tag;
};

#endif // __NewUnit_H__
