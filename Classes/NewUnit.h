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

class NewUnitLayer : public CCLayerColor, CCTextFieldDelegate
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
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void registerWithTouchDispatcher();

	static NewUnitLayer* create(string unitID);

	//���û������������ʱ�Ļص�����
	//���ü���false; �����ü���true
	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF* sender);

	//���û��ر��������ʱ�Ļص�����
	//�رռ���false; ���رռ���true
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF* sender);

	//���û�����ʱ�Ļص�����
	//���������ַ�false; �����������ַ�true
	virtual bool onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen);

	//���û�ɾ������ʱ�Ļص�����
	//����ɾ���ַ�false; ������ɾ���ַ�true
	virtual bool onTextFieldDeleteBackward(CCTextFieldTTF* sender, const char* delText, int nLen);


	/**
	* �޸�xml�ļ��к��ֶ�Ӧproficiencyֵ
	* @param character Ҫ�޸�profֵ��Ӧ����
	* @param proficiencyҪ�޸ĵ���ֵ
	* @return
	*/
	bool setProficiency(string character,string proficiency);
	
	CC_SYNTHESIZE_RETAIN(CCEditBox*, m_editBox, m_editBox);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_TextList, m_TextList);

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
