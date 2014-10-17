#ifndef _TcharacterDrawnode_H__
#define _TcharacterDrawnode_H__

#include "cocos2d.h"
#include "Character.h"
#include "StrokeDrawnode.h"
#include "CharacterEntity.h"
#include "CharacterExtend.h"
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


	virtual bool init(string hz,CCSize showrect,CharacterExtend* p);

	/**
	* �ú��ֺ���ʾ���򴴽�TcharacterDrawnode
	* @param hz
	* @param showrect
	* @return
	*/
	static TcharacterDrawnode* create(string hz,CCSize showrect,CharacterEntity* p);

	static TcharacterDrawnode* create(string hz,CCSize showrect,CharacterExtend* p);

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

	/**
		������������xml�б�׼�����������Ϣ
	*/
	string getCharacterStandardInfo();

	CC_SYNTHESIZE_RETAIN(CCArray*,strokedrawList,strokedrawList);
private:
	CCSize showRect;				//���ݴ������ʾ��Χ������ʾ��Χ
	Character m_character;			//���ݺ��ֶ�ȡ�ַ�xml�ļ�������Character
	int visibleIndex;
	Character myChar;
};


#endif
