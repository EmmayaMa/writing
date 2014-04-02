#ifndef __SqliteHelper_H__
#define __SqliteHelper_H__

#include "cocos2d.h"
#include "sqlite3.h"
using namespace std;
USING_NS_CC;

class SqliteHelper
{
public:
	//��������һ��db���ݿ� dbΪ���ݿ������
	static void initDB(const char* db);
	//�����жϱ���Ƿ����
	static bool tableIsExist(string name);
	//��������һ������Ϊname�ı�񣬴���ʱ����ƥ��ʱ���иñ�Ĵ�����������򲻴���
	static void createTable(string sql,string name);
	//����ɾ��һ�ű���Ϊname�ı��ɾ��ʱ����ƥ���Ƿ��иñ�Ĵ��������������ִ��ɾ������
	static void deleteTable(string sql,string name);
	//��������в���һ������
	static void insertData(string sql);
	//���������ɾ��һ������
	static void deleteData(string sql);
	//����������޸�һ������
	static void updateData(string sql);
	//��ȡһ����¼������
	static int getDataCount(string sql);
	//��ȡһ����¼����Ϣ
	static void getDataInfo(string sql,CCObject* pSend);

	//�رմ򿪵����ݿ�
	static void closeDB();
private:

};


#endif