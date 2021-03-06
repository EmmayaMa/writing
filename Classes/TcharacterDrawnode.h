#ifndef _TcharacterDrawnode_H__
#define _TcharacterDrawnode_H__

#include "cocos2d.h"
#include "Character.h"
#include "StrokeDrawnode.h"
#include "CharacterEntity.h"
#include "CharacterExtend.h"
USING_NS_CC;

// 继承CCNode,用于显示正确汉字                                                                     */
class TcharacterDrawnode : public CCNode
{
public:
	TcharacterDrawnode();
	~TcharacterDrawnode();

	/**
	* 实现CCNode绘图函数，根据自身笔画列表绘图
	* @return
	*/
	virtual void draw();
	/**
	* 用汉字和显示区域初始化TcharacterDrawnode
	* @param hz 
	* @param showrect
	* @return
	*/
	virtual bool init(string hz,CCSize showrect,CharacterEntity* p);


	virtual bool init(string hz,CCSize showrect,CharacterExtend* p);

	/**
	* 用汉字和显示区域创建TcharacterDrawnode
	* @param hz
	* @param showrect
	* @return
	*/
	static TcharacterDrawnode* create(string hz,CCSize showrect,CharacterEntity* p);

	static TcharacterDrawnode* create(string hz,CCSize showrect,CharacterExtend* p);

	/**
	* 返回当前正字Character
	* @return
	*/
	Character getCharacter(){return m_character;}

	/**
	 * get all strokes points count for animation
	 * @return
	 */
	int getPointsCount();

	void setVisibleIndex(int vi);
	int getVisibleIndex()    { return visibleIndex; }

	/**
		产生整个汉字xml中标准汉字坐标点信息
	*/
	string getCharacterStandardInfo();

	CC_SYNTHESIZE_RETAIN(CCArray*,strokedrawList,strokedrawList);

private:
	CCSize showRect;				//根据传入的显示范围定义显示范围
	Character m_character;			//根据汉字读取字符xml文件，构造Character
	int visibleIndex;
	Character myChar;
	CCSprite* tiangzige;
};


#endif
