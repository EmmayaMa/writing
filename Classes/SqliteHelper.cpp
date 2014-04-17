#include "SqliteHelper.h"
#include "CharacterEntity.h"

sqlite3 *pDB = NULL;//���ݿ�ָ�� 
char * errMsg = NULL;//������Ϣ 
std::string sqlstr;//SQLָ�� 
int result;//sqlite3_exec����ֵ		

void SqliteHelper::initDB(const char* db){
	//��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�
	result = sqlite3_open(db,&pDB);
	if (result != SQLITE_OK)
	{
		CCLog("open sqlite failed,�����ݿ�ʧ�ܣ�������error:%d ������ԭ��reason:%s\n" , result, errMsg );
	}else{
		CCLog("open sqlite success~ no:%d",result);
	}
}

//tableIsExist�Ļص�����
int isExisted( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
	bool *isExisted_=(bool*)para; 
	*isExisted_=(**column_value)!='0'; 
	return 0; 
}

bool SqliteHelper::tableIsExist( string name )
{
	if (pDB!=NULL)
	{
		//�жϱ��Ƿ����
		bool tableIsExisted;
		sqlstr = "select count(type) from sqlite_master where type='table' and name ='"+name+"'";
		result =sqlite3_exec(pDB,sqlstr.c_str(),isExisted,&tableIsExisted,&errMsg);
		return tableIsExisted;
	}
	return false;
}

//�����ݿ����ж���Ϊname�ı�ʾ����ڣ�����������򴴽����ű�
//@ʾ�����string sqls = "create table user(id integer,username text,password text)";
void SqliteHelper::createTable( string sql,string name )
{
	if (!tableIsExist(name))
	{
		//����������IDΪ���������Զ����� 
		result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
		if( result != SQLITE_OK ) 
			CCLog( "������ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
	}
}

//ɾ�����
//@ʾ�����sqlstr="drop table name"; 
void SqliteHelper::deleteTable( string sql,string name )
{
	if (tableIsExist(name))
	{
		result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
		if( result != SQLITE_OK ) 
			CCLog( "������ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
	}
}


//��������
//@ʾ�����sqlstr=" insert into MyTable_1( name ) values ( '������' ) "; 
void SqliteHelper::insertData( string sql ){
	result = sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg ); 
	if(result != SQLITE_OK ) 
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
}


//ɾ������
//@ʾ�����sqlstr="delete from MyTable_1 where ID = 2"; 
void SqliteHelper::deleteData( string sql )
{
	result=sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
	if(result != SQLITE_OK ) 
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
}

//�޸�����
//@ʾ�����        sqlstr="update MyTable_1 set name='������' where ID = 3"; 
void SqliteHelper::updateData( string sql )
{
	result = sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
	if(result != SQLITE_OK ) 
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
}

//getDataCount�Ļص�����
int loadRecordCount( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
	int *count=(int*)para; 
	*count=n_column; 
	return 0; 
}

//��ȡ��¼������
//@ʾ�����string sqlsssss = "select count(*) from user";
//@ʾ�����  ȡ�ñ���ֶε����string sqlsssss = "select * from user";
int SqliteHelper::getDataCount( string sql )
{
	int count=0; 
	sqlite3_exec( pDB, sql.c_str() ,     loadRecordCount, &count, &errMsg );
	return count;
}

//getDataInfo�Ļص�����
int loadRecord( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
// 	CCLog("ID=%s,name=%s,password=%s,word=%s",column_value[0],column_value[1],column_value[2],column_value[3]);
	CCLog("ID=%s name=%s",column_value[0],column_value[1]);
	((CharacterEntity*)para)->setID(CCInteger::create(atoi(column_value[0])));
	((CharacterEntity*)para)->setName(ccs(column_value[1]));
	((CharacterEntity*)para)->setXML(ccs(column_value[2]));
	return 0;
}
//��ȡһ����¼����Ϣ ���е�pSend��һ��ʵ���������Ժ�����Զ���һ���̳���CCObject�������������������ݿ���ȡ����������
void SqliteHelper::getDataInfo( string sql,CCObject *pSend )
{
	int ret = sqlite3_exec( pDB, sql.c_str() , loadRecord, pSend, &errMsg );
	CCLog("return no:%d error:%s",ret,errMsg);
}

//�ر����ݿ�
void SqliteHelper::closeDB()
{
	sqlite3_close(pDB); 
}
