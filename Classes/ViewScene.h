#ifndef __ViewScene_H__
#define __ViewScene_H__

#include "cocos2d.h"
#include "SQLiteData.h"
#include "HcharacterDrawnode.h"
#include "PopCancelLayer.h"
#include "../CocosWidget/cocos-widget.h"
#include <algorithm>
using namespace cocos2d::cocoswidget;
using namespace std;
USING_NS_CC;

class ViewScene : public CCLayerColor
{
public:
	ViewScene();
	~ViewScene();
	static CCScene* scene(string unit_id, string zi_id, string curChar);
	static ViewScene* create(string unit_id, string zi_id, string curChar);
	virtual bool init(string unit_id, string zi_id, string curChar);
	
	string getCurChar()		{ return currentChar; }
private:
	CCObject* gridViewDataSource(CCObject* pContentView, unsigned int idx);
	void buttonClick(CCObject* pSender);
	void deleteBtnClick(CCObject* pSender);
	void checkBoxClick(CCObject* pSender);
	void back(CCObject* pSender);
	void dlgCallback(CCNode* pNode);
	CGridView* pGridView;
	vector< vector <string> > Notes;		//store the data read from sqlite
	string unit_id;							//需要根据 unit_id 和 zi_id 来显示
	string zi_id;
	string currentChar;						//当前汉字
	int writingCount;						//记录总共的Note 数量为Notes 的 size
	int selectDeleteNote;					//需要删除的元素
	vector<int> dltList;					//需要删除的元素列表
};

#endif
