#ifndef __SQLiteData_H_
#define __SQLiteData_H_

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class SQLiteData
{
public:

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
	* @param hz ������ ��ӦziName����
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

	/**
	* ��ȡ���ݿ���һ��16���֣���������
	* @param index id�ţ�����1
	* @return vector<string>
	*/
	static vector<string> getGroupCharacter(string index);

	/**
	* ����һ���е�indexOfCharacter������
	* @param index �к�
	* @param indexOfCharacter �ڼ�������
	* @param character ����
	* @return true�ɹ� falseʧ��
	*/
	static bool updateGroupCharacter(string index, string indexOfCharacter, string character);

	/**
	* �����ݿ��в�ѯindex��Unit��ǰcount���֣����浽������Ŷ��
	* @param index Unit�ı��
	* @param count �õ�Ԫ��ǰcount������
	* @return
	*/
	static vector<vector<string>> getUnit(string index,int count=16);

};



#endif