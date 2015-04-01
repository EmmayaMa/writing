#ifndef __Hcharacter_H__
#define __Hcharacter_H__

#include "cocos2d.h"
#include "cocos-widget.h"
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
	virtual void onExit();
	virtual void onEnter();

	/**
	* convert512 ת����512*512 ��������ԭ����õ����Ͻ�
	* @param p
	* @return
	*/
	CCPoint convert512(CCPoint p);
	string floatToString(float f);
	void judge();
	void reloadChar();
	float getWrongPercent();

	CC_SYNTHESIZE_RETAIN(HcharacterDrawnode*,m_HDrawnode,m_HDrawnode);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, bihuaCount,bihuaCount);
	CC_SYNTHESIZE_RETAIN(CCSprite* , m_sprite_draw, Sprite);
	CC_SYNTHESIZE_RETAIN(CCSprite* , m_sprite_info, InfoSprite);
	CC_SYNTHESIZE_RETAIN(CharacterExtend* , m_exChar, ExChar);
private:
	void rewrite(CCObject* pSender);
	void zoomin(CCObject* pSender);
	void zoomout(CCObject* pSender);
	string hanzi;
	void writeWrong();
	void writeRight();
	int writeCount;
	int wrongCount;
	float scale;
};


#endif
