#ifndef __SqliteHelper_H__
#define __SqliteHelper_H__

#include "cocos2d.h"
#include "sqlite3.h"
using namespace std;
USING_NS_CC;

class SQLiteHelper
{
public:
	/**
	* ��������һ��db���ݿ� dbΪ���ݿ������
	* @param db
	* @return
	*/
	static void initDB(const char* db);

	/**
	* �����жϱ���Ƿ����
	* @param name
	* @return
	*/
	static bool tableIsExist(string name);

	/**
	* ��������һ������Ϊname�ı�񣬴���ʱ����ƥ��ʱ���иñ�Ĵ�����������򲻴���
	* @param sql
	* @param name
	* @return
	*/
	static void createTable(string sql,string name);

	/**
	* ����ɾ��һ�ű���Ϊname�ı��ɾ��ʱ����ƥ���Ƿ��иñ�Ĵ��������������ִ��ɾ������
	* @param sql
	* @param name
	* @return
	*/
	static void deleteTable(string sql,string name);
	
	/**
	* ��������в���һ������
	* @param sql @ʾ�����sqlstr=" insert into MyTable(name) values( '������')"; 
	* @return ���ز��������е�id
	*/
	static int insertData(string sql);

	/**
	* ���������ɾ��һ������
	* @param sql @ʾ�����sqlstr="delete from MyTable where ID = 2"; 
	* @return
	*/
	static void deleteData(string sql);

	/**
	* ����������޸�һ������
	* @param sql
	* @return
	*/
	static void updateData(string sql);

	/**
	* ��ȡһ����¼������
	* @ʾ�����string sql = "select count(*) from user";
	* @ʾ�����  ȡ�ñ���ֶε����string sqlsssss = "select * from user";
	* @param sql
	* @return
	*/
	static int getDataCount(string sql);

	/**
	* ��ȡһ����¼����Ϣ
	* @param sql
	* @param pSend
	* @return
	*/
	static void getDataInfo(string sql,CCObject* pSend);

	/**
	* ��ȡziData����һ������
	* @param sql
	* @param p
	* @return
	*/
	static void getZiDataInfo(string sql,CCObject* p);

	/**
	* �ɽ������ȡ
	* @param sql
	* @param p
	* @return
	*/
	static void getZiDataInfoExtend(string sql,CCObject* p);

	/**
	* ��ȡstrokeFunc����һ������
	* @param sql
	* @param funcbody
	* @return
	*/
	static void getstrokeFunc(string sql,CCObject* funcbody);

	/**
	* �رմ򿪵����ݿ�
	* @return
	*/
	static void closeDB();

	/**
	* ������groupCharacter�л�ȡһ��16��������
	* @param sql
	* @return vector<string>
	*/
	static vector<string> getGroupCharacter(string sql);

	/**
	* �����ݿ��л�ȡһ��Ԫ����
	* @param sql ���
	* @return
	*/
	static string getUnit(string sql);

	/**
	* 
	* @param sql
	* @return
	*/
	static vector<string> getUnitIDs(string sql);

	/**
	* ��ziNotes�� ��ȡ����
	* @param sql sql���
	* @return
	*/
	static vector<vector <string> > getNote(string sql);
private:

};


#endif