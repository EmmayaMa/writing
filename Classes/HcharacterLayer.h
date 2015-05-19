#ifndef __Hcharacter_H__
#define __Hcharacter_H__

#include "cocos2d.h"
#include "../CocosWidget/cocos-widget.h"
#include "HcharacterDrawnode.h"
#include "CharacterExtend.h"
USING_NS_CC;
using namespace cocos2d::cocoswidget;

class HcharacterLayer : public CCLayer
{
public:
	HcharacterLayer();
	~HcharacterLayer();
	static HcharacterLayer* create(string hanzi,CCSprite* tianzige_draw);
	virtual bool init(string hanzi,CCSprite* tianzige_draw);
	virtual void onEnter();
	virtual void onExit();

	/**
	* convert512 ת����512*512 ��������ԭ����õ����Ͻ�
	* @param p
	* @return
	*/
	CCPoint convert512(CCPoint p);
	void judge();
	void reloadChar();				//���¼��غ�����Ϣ
	float getWrongPercent();
	void isJudge(bool isjudge);
	string getPointsOutput()	{ return pointsOutput; }
	string getOriginPoints()	{ return pointsOrigin; }

	/**
	* clear all writing like function rewrite(CCOject* pSender)
	* @return
	*/
	void clearWriting();

	CC_SYNTHESIZE_RETAIN(HcharacterDrawnode*,m_HDrawnode,m_HDrawnode);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, bihuaCountAndTotal,bihuaCountAndTotal);
	CC_SYNTHESIZE_RETAIN(CCSprite* , m_sprite_draw, Sprite);
	CC_SYNTHESIZE_RETAIN(CCSprite* , m_sprite_info, InfoSprite);
	CC_SYNTHESIZE_RETAIN(CharacterExtend* , m_exChar, ExChar);
private:
	/**
	* ��д�ص�����
	* @param pSender
	* @return
	*/
	void rewrite(CCObject* pSender);
	/**
	* �Ŵ�ص�����
	* @param pSender
	* @return
	*/
	void zoomin(CCObject* pSender);			//
	/**
	* ��С�ص�����
	* @param pSender
	* @return
	*/
	void zoomout(CCObject* pSender);		//
	void writeWrong();
	void writeRight();
	int writeCount;				//��д����
	int wrongCount;				//�������
	string hanzi;				//����ò�ʹ�ú���
	float scale;				//���ű���
	bool ijudge;				//�Ƿ����� false�����У�true����
	string pointsOutput;		//����ַ���
	string pointsOrigin;		//��д����Origin�ַ��� δ��Points �ı���
	int totalCount;				//�ú����ܹ��еıʻ���
};


#endif
