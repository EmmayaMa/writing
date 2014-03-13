#ifndef __LianxiScene_H__
#define __LianxiScene_H__

#include "cocos2d.h"
#include "TouchLayer.h"
#include "BackgroundLayer.h"
#include "TcharacterLayer.h"
#include "HcharacterLayer.h"
USING_NS_CC;


class LianxiScene : public CCScene
{
public:
	LianxiScene();
	LianxiScene(string hanzi);
	~LianxiScene();
	CREATE_FUNC(LianxiScene);
	static LianxiScene* create(string hanzi);
	virtual bool init();

	string testCharacter;			//��ǰ������ϰ�ĺ����ַ�

	BackgroundLayer* backgroundLayer;		//����ͼ��
	TouchLayer* touchLayer;			//�����¼���Ӧ��
	TcharacterLayer* TLayer;			//����ͼ��
	HcharacterLayer* HLayer;
private:

};



#endif