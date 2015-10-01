#ifndef __SQLiteData_H_
#define __SQLiteData_H_

#include "cocos2d.h"
#include "SqliteHelper.h"
#include "CharacterEntity.h"
#include "strokeFunc.h"
#include "CharacterExtend.h"
#include "tools/DataTool.h"
#include <vector>
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
//	static string getstrokeFunc(string strokeID);

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
	static vector<vector <string> > getUnit(string unit_id,int count=16);

	/**
	* ����һ��Ԫ����
	* @param index ��ԪID
	* @param unit ��Ԫ������
	* @return
	*/
	static bool updateUnit(string unit_id,vector<vector <string> > unit);

	/**
	* �����ݿ��в���һ��Ԫ����
	* @param unit ������unit������
	* @return ���ظ�Unit��ID
	*/
	static string insertUnit(vector<vector <string> > unit);

	/**
	* �����ݿ��в���һ��Ԫ����
	* @param unit_info �õ�Ԫ�Ļ�����Ϣ����
	* @param unit ������unit������
	* @return ���ظ�Unit��ID
	*/
    static string insertUnit(string unit_info,vector<vector <string> > unit);

	/**
	* ɾ�����ݿ���unit id�ĵ�Ԫ����
	* @param unit_id
	* @return
	*/
	static bool deleteUnit(string unit_id);

	/**
	* ��ȡUnit������
	* @return
	*/
	static int getUnitCount();

	/**
	* ��ȡ���ݿ��е�ԪID
	* @return
	*/
	static vector<string> getUnitIDs();

	/**
	* �����ݿ��в���һ���ʼǼ�¼
	* @param unit_id	��Ԫid
	* @param zi_id		����id
	* @param note		�ʼ� ��������Ϣ
	* @return			���ز������id
	*/
	static string insertNote(string unit_id,string zi_id,string note);

	/**
	* �����ݿ���ɾ��һ����¼
	* @param id	��¼��id
	* @return
	*/
	static bool deleteNote(string id);

	/**
	* �����ݿ� ziNotes ���ж�ȡ unit_id ���� ziid ����д����ֵ
	* @param unit_id ��ԪID
	* @param zi_id ��ID��ÿ�����ֵ�ID��Ψһ��
	* @return vector<vector <string> >
	*/
	static vector<vector <string> > getNote(string unit_id, string zi_id);

};



#endif
