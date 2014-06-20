#include "LianxiScene.h"
#include "CharacterEntity.h"
#include "SQLiteData.h"
#include <algorithm>
using namespace std;

typedef enum layers
{
	kBgLayerTag,
	kHLayerTag,
	kTLayerTag,
	kTouchLayerTag
};

LianxiScene::LianxiScene(string hanzi):backgroundLayer(NULL),
	touchLayer(NULL),
	TLayer(NULL),
	HLayer(NULL)
{
	this->testCharacter = hanzi;
	p = new CharacterEntity();
}

LianxiScene::~LianxiScene()
{
	CCLog("~~LianxiScene %d",  this->m_uReference);
	CC_SAFE_RELEASE(backgroundLayer);
	CC_SAFE_RELEASE(TLayer);
	CC_SAFE_RELEASE(HLayer);
	CC_SAFE_RELEASE(touchLayer);
}

LianxiScene* LianxiScene::create(string hanzi){
	LianxiScene* pRet = new LianxiScene(hanzi);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}else{
        CC_SAFE_DELETE(pRet);        
		return NULL;
	}
}

bool LianxiScene::init(){
	bool bRet = false;
	do
	{
		this->setbackgroundLayer(BackgroundLayer::create());
		CC_BREAK_IF(!backgroundLayer);
		backgroundLayer->setTag(kBgLayerTag);
		this->addChild(backgroundLayer);

		this->setTLayer(TcharacterLayer::create(backgroundLayer->tianzige));
		CC_BREAK_IF(!TLayer);
		TLayer->setTag(kTLayerTag);
		//TLayer->setSprite(backgroundLayer->tianzige);			����������tianzige����������Ϣͼ��
		this->addChild(TLayer);

		this->setHLayer(HcharacterLayer::create(testCharacter,backgroundLayer->tianzige_draw));
		CC_BREAK_IF(!HLayer);
		HLayer->setTag(kHLayerTag);
		this->addChild(HLayer);
		
		this->settouchLayer(TouchLayer::create(TLayer,HLayer));
		CC_BREAK_IF(!touchLayer);
		touchLayer->setTag(kTouchLayerTag);
		this->addChild(touchLayer);

		CCLog("LianxiScene ref: %d",this->m_uReference);

		CC_BREAK_IF(!CCScene::init());
		bRet = true;
	} while (0);

	SQLiteData::getHanziData(this->testCharacter,p);
	CCString* temp = p->getSEQ();
	CCLog("seq %s",temp->getCString());
	string str(temp->getCString());
	vector<string> strvec = SQLiteData::splitStrokeSeq(str);
	//ȥ��
	std::sort(strvec.begin(),strvec.end());
	strvec.erase(std::unique(strvec.begin(),strvec.end()),strvec.end());
	vector<string>::iterator iter = strvec.begin(),iter2 = strvec.end();

	while (iter != iter2)
	{
		funcs += SQLiteData::getstrokeFunc(*iter);
		funcs += "\n";
		iter ++;
	}

	return bRet;
}
