#ifndef __ACTIONA0001_H__
#define __ACTIONA0001_H__

#include "cocos2d.h"
#include "ShuipingErrorNode.h"
USING_NS_CC;

class ActionA0001 : public CCActionInterval
{
public:
	ActionA0001();
	~ActionA0001();

	/**
	* ����ActionA0001����
	* @param duration ����ʱ��
	* @return
	*/
	static ActionA0001* create(float duration);
	virtual void update(float time);
	bool init(float duration);
	void startWithTarget(CCNode *pTarget);

private:
	float length;				// ��¼�������ֵ
	float bigY;					// ��¼���ϵ�Yֵ
};


#endif