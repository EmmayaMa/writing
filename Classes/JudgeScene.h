#ifndef __JudgeScene_H__
#define __JudgeScene_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "TcharacterLayer.h"
#include "HcharacterLayer.h"	
#include "TouchLayer.h"
#include "CharacterExtend.h"
#include "JudgeLayer.h"
USING_NS_CC;
using namespace std;

class JudgeScene : public CCScene
{
public:
	JudgeScene();
	/**
	* ����unit_id �� hanzis �б�
	* @param unit_id ��Ӧ���ݿ��е�ԪID
	* @param hanzis �����б�
	* @return
	*/
	JudgeScene(string unit_id,vector<string> hanzis);
	~JudgeScene();
	static JudgeScene* create(string unit_id,vector<string> hanzis);
	virtual bool init();

	CC_SYNTHESIZE_RETAIN(BackgroundLayer*,backgroundLayer,backgroundLayer);
	CC_SYNTHESIZE_RETAIN(TouchLayer*,touchLayer,touchLayer);
	CC_SYNTHESIZE_RETAIN(TcharacterLayer*,TLayer,TLayer);
	CC_SYNTHESIZE_RETAIN(HcharacterLayer*,HLayer,HLayer);
	CC_SYNTHESIZE_RETAIN(CharacterExtend*,ext_p,CharacterExt);

	CC_SYNTHESIZE_RETAIN(JudgeLayer* , judgeLayer , JudgeLayer);

	/**
	* ��һ������
	* @return
	*/
	void previous();

	/**
	* ��һ������
	* @return
	*/
	void next();

	
	/**
	* �����Ƿ�������д trueΪ���� falseΪ������
	* @param isjudge
	* @return
	*/
	void setIsJudge(bool isjudge);
	bool getIsJudge()	{ return b_isJudge; }

	string getUnitID()	{ return unit_id;}
	string getZiID()	{ return zi_id; }
	string getCharacter()		{ return currentCharacter;}

private:

	void lastCharacter(CCNode* pNode);	//��Ԫ���һ�����ֻص�����
	string unit_id;						//���浥Ԫid
	string zi_id;
	vector<string> hanziList;			//���溺���б�
	string currentCharacter;			//��ǰ��д����
	int index;							//���浱ǰ�������
	bool b_isJudge;						//��ǰScene�Ƿ��ж� false Ϊ������д
};




#endif