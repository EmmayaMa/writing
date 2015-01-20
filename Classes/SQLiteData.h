#ifndef __SQLiteData_H_
#define __SQLiteData_H_

#include "cocos2d.h"
#include "SqliteHelper.h"
#include "CharacterEntity.h"
#include "strokeFunc.h"
#include "CharacterExtend.h"

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
//	static vector<string> getGroupCharacter(string index);

	/**
	* ����һ���е�indexOfCharacter������
	* @param index �к�
	* @param indexOfCharacter �ڼ�������
	* @param character ����
	* @return true�ɹ� falseʧ��
	*/
//	static bool updateGroupCharacter(string index, string indexOfCharacter, string character);

	// usage of these two functions
	// 	vector<string> groupCharacter = SQLiteData::getGroupCharacter(DataTool::intTostring(0));
	//	SQLiteData::updateGroupCharacter(DataTool::intTostring(1),DataTool::intTostring(1),DataTool::getChinese("zi"));


	/**
	* �����ݿ��в�ѯindex��Unit��ǰcount���֣����浽������Ŷ��
	* @param index Unit�ı��
	* @param count �õ�Ԫ��ǰcount������
	* @return
	*/
	static vector<vector<string>> getUnit(string index,int count=16);

	/**
	* ����һ��Ԫ����
	* @param index ��ԪID
	* @param unit ��Ԫ������
	* @return
	*/
	static bool updateUnit(string index,vector<vector<string>> unit);
};



#endif