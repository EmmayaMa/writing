#ifndef __Hcharacter_H__
#define __Hcharacter_H__

#include "cocos2d.h"
#include "HcharacterDrawnode.h"
USING_NS_CC;

class HcharacterLayer : public CCLayer
{
public:
	HcharacterLayer();
	~HcharacterLayer();
	static HcharacterLayer* create(string hanzi,CCSprite* tianzige_draw);
	virtual bool init(string hanzi,CCSprite* tianzige_draw);
	virtual void onExit();
	virtual void onEnter();
	//************************************
	// Method:    convert512 ת����512*512 ��������ԭ����õ����Ͻ�
	// FullName:  HcharacterLayer::convert512
	// Access:    public 
	// Returns:   cocos2d::CCPoint
	// Qualifier:
	// Parameter: CCPoint p
	//************************************
	CCPoint convert512(CCPoint p);
	string floatToString(float f);
	void judge();

	CC_SYNTHESIZE_RETAIN(HcharacterDrawnode*,m_HDrawnode,m_HDrawnode);
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, bihuaCount,bihuaCount);
	CC_SYNTHESIZE_RETAIN(CCSprite* , m_sprite_draw, Sprite);
	CC_SYNTHESIZE_RETAIN(CCSprite* , m_sprite_info, InfoSprite);
private:
	void rewrite(CCObject* pSender);
	string hanzi;
};


#endif
