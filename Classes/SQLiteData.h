#ifndef __SQLiteData_H_
#define __SQLiteData_H_

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class SQLiteData
{
public:
	SQLiteData();
	~SQLiteData();

	/**
	* ��ȡ���ݿ��к�����Ϣ
	* @param hz
	* @param p
	* @return
	*/
	static void getHanziData(string hz,CCObject* p);

	/**
	* ��ȡ������strokeFunc����Ϣ
	* @param strokeID
	* @return
	*/
	static string getstrokeFunc(string strokeID);

	/**
	* �������ݿ���strokeIDSeq�ֶ�
	* @param seq
	* @return
	*/
	static vector<string> splitStrokeSeq(string seq);

	/**
	* ��ȡ�ɽ�����ĺ���
	* @param hz
	* @param p
	* @return
	*/
	static void getHanziDataExtend(string hz,CCObject* p);

	/**
	* judge a Character is exist in db
	* @param hz
	* @return
	*/
	static bool isExist(string hz);
};



#endif