#ifndef __ceshiLayer_H__
#define __ceshiLayer_H__

#include "cocos2d.h"
USING_NS_CC;

class ceshiLayer : public CCLayer
{
public:
	ceshiLayer();
	~ceshiLayer();
	CREATE_FUNC(ceshiLayer);
	bool init();
	void SaveProToFile(float pro);
private:
	void menuNext(CCObject* pSender);
	void menuPrevious(CCObject* pSender);
};



#endif