#ifndef __CeshiScene_H__
#define __CeshiScene_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "TcharacterLayer.h"
#include "HcharacterLayer.h"
#include "TouchLayer.h"
#include "CharacterExtend.h"
USING_NS_CC;
using namespace std;

class CeshiScene : public CCScene
{
public:
	CeshiScene();
	~CeshiScene();
	static CeshiScene* create(string wallfilename,vector<string> hanzis);
	virtual bool init(string wallfilename,vector<string> hanzis);
	virtual void onEnter();
	virtual void onExit();


	CC_SYNTHESIZE_RETAIN(BackgroundLayer*,backgroundLayer,backgroundLayer);
	CC_SYNTHESIZE_RETAIN(TouchLayer*,touchLayer,touchLayer);
	CC_SYNTHESIZE_RETAIN(TcharacterLayer*,TLayer,TLayer);
	CC_SYNTHESIZE_RETAIN(HcharacterLayer*,HLayer,HLayer);
	//	CC_SYNTHESIZE_RETAIN(CharacterEntity*,p,CharacterP);
	CC_SYNTHESIZE_RETAIN(CharacterExtend*,ext_p,CharacterExt);

private:
	string wallfilename;
	vector<string> hanzis;
	string curhanzi;
	string funcs;						//��ǰ������Ҫʹ�õ������бʻ�lua���й���

};




#endif