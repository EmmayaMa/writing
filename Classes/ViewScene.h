#ifndef __ViewScene_H__
#define __ViewScene_H__

#include "cocos2d.h"
#include "SQLiteData.h"
#include "HcharacterDrawnode.h"
#include "PopCancelLayer.h"
#include "../CocosWidget/cocos-widget.h"
using namespace cocos2d::cocoswidget;
using namespace std;
USING_NS_CC;

class ViewScene : public CCLayerColor
{
public:
	ViewScene();
	~ViewScene();
	static CCScene* scene(string unit_id, string zi_id);
	static ViewScene* create(string unit_id, string zi_id);
	virtual bool init(string unit_id, string zi_id);
	

private:
	CCObject* gridViewDataSource(CCObject* pContentView, unsigned int idx);
	void buttonClick(CCObject* pSender);
	void back(CCObject* pSender);
	void dlgCallback(CCNode* pNode);
	CGridView* pGridView;
	vector< vector <string> > Notes;		//store the data read from sqlite
	string unit_id;			//��Ҫ���� unit_id �� zi_id ����ʾ
	string zi_id;
	int writingCount;		//��¼�ܹ���Note ����ΪNotes �� size
	int selectDeleteNote;
};

#endif