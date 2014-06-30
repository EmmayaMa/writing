#ifndef _TcharacterDrawnode_H__
#define _TcharacterDrawnode_H__

#include "cocos2d.h"
#include "Character.h"
#include "StrokeDrawnode.h"
#include "CharacterEntity.h"
USING_NS_CC;

/************************************************************************/
/* �̳�CCNode,������ʾ��ȷ����                                                                     */
/************************************************************************/
class TcharacterDrawnode : public CCNode
{
public:
	TcharacterDrawnode();
	~TcharacterDrawnode();
	/**
	* ʵ��CCNode��ͼ��������������ʻ��б��ͼ
	* @return
	*/
	virtual void draw();
	/**
	* �ú��ֺ���ʾ�����ʼ��TcharacterDrawnode
	* @param hz 
	* @param showrect
	* @return
	*/
	virtual bool init(string hz,CCSize showrect,CharacterEntity* p);
	/**
	* �ú��ֺ���ʾ���򴴽�TcharacterDrawnode
	* @param hz
	* @param showrect
	* @return
	*/
	static TcharacterDrawnode* create(string hz,CCSize showrect,CharacterEntity* p);

//	CREATE_FUNC(TcharacterDrawnode);
// 	vector<StrokeDrawnode*> strokedrawList;

	/**
	* ���ص�ǰ����Character
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

	CC_SYNTHESIZE_RETAIN(CCArray*,strokedrawList,strokedrawList);
private:
	CCSize showRect;				//���ݴ������ʾ��Χ������ʾ��Χ
	Character m_character;			//���ݺ��ֶ�ȡ�ַ�xml�ļ�������Character
	int visibleIndex;
};


#endif
