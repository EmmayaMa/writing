#include "SqliteHelper.h"
#include "CharacterEntity.h"
#include "strokeFunc.h"
#include "CharacterExtend.h"

sqlite3 *pDB = NULL;//���ݿ�ָ�� 
char * errMsg = NULL;//������Ϣ 
std::string sqlstr;//SQLָ�� 
int result;//sqlite3_exec����ֵ		

void SQLiteHelper::initDB(const char* db){
	//��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�
	result = sqlite3_open(db,&pDB);
	if (result != SQLITE_OK)
	{
		CCLog("open sqlite failed,error:%d ��error reason:%s\n" , result, errMsg );
	}else{
		CCLog("open sqlite success~ code:%d",result);
	}
}

//tableIsExist�Ļص�����
int isExisted( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
	bool *isExisted_=(bool*)para; 
	*isExisted_=(**column_value)!='0'; 
	return 0; 
}

bool SQLiteHelper::tableIsExist( string name )
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
void SQLiteHelper::createTable( string sql,string name )
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
void SQLiteHelper::deleteTable( string sql,string name )
{
	if (tableIsExist(name))
	{
		result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
		if( result != SQLITE_OK ) 
			CCLog( "������ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
	}
}

int SQLiteHelper::insertData( string sql ){
	result = sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg ); 
	if(result != SQLITE_OK ) 
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg );
	sqlite3_int64 id = sqlite3_last_insert_rowid(pDB);
	return id;
}

void SQLiteHelper::deleteData( string sql )
{
	result=sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
	if(result != SQLITE_OK ) 
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
}

//�޸�����
//@ʾ�����        sqlstr="update MyTable_1 set name='������' where ID = 3"; 
void SQLiteHelper::updateData( string sql )
{
	result = sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
	if(result != SQLITE_OK ) 
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
}

//getDataCount�Ļص�����
int loadRecordCount( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
	int *count=(int*)para; 
	*count=atoi(column_value[0]);
	return 0;
}

int SQLiteHelper::getDataCount( string sql )
{
	int count=0;
	sqlite3_exec( pDB, sql.c_str() , loadRecordCount, &count, &errMsg );
	if (errMsg)
	{
		sqlite3_free(errMsg);
	}
	return count;
}

//getDataInfo�Ļص�����
int loadRecord( void * para, int n_column, char ** column_value, char ** column_name)
{ 
// 	CCLog("ID=%s,name=%s,password=%s,word=%s",column_value[0],column_value[1],column_value[2],column_value[3]);
	CCLog("ID=%s name=%s",column_value[0],column_value[1]);
	((CharacterEntity*)para)->setID(CCInteger::create(atoi(column_value[0])));
	((CharacterEntity*)para)->setName(ccs(column_value[1]));
	((CharacterEntity*)para)->setXML(ccs(column_value[2]));
	((CharacterEntity*)para)->setRules(ccs(column_value[3]));
	return 0;
}
//��ȡһ����¼����Ϣ ���е�pSend��һ��ʵ���������Ժ�����Զ���һ���̳���CCObject�������������������ݿ���ȡ����������
void SQLiteHelper::getDataInfo( string sql,CCObject *pSend )
{
	int ret = sqlite3_exec( pDB, sql.c_str() , loadRecord, pSend, &errMsg );
	CCLog("return getDataInfo error code:%d error:%s",ret,errMsg);
}

int loadziRecord(void * para, int n_column, char ** column_value, char ** column_name){
	((CharacterEntity*)para)->setID(CCInteger::create(atoi(column_value[0])));		//ID
	((CharacterEntity*)para)->setName(ccs(column_value[1]));						//ziName
	((CharacterEntity*)para)->setSEQ(ccs(column_value[2]));							//strokeIDSeq
	CCLog("%s",column_value[2]);
	((CharacterEntity*)para)->setRules(ccs(column_value[3]));						//rules
	((CharacterEntity*)para)->setXML(ccs(column_value[4]));							//xml
	return 0;
}

void SQLiteHelper::getZiDataInfo(string sql,CCObject* p){
	int ret = sqlite3_exec(pDB , sql.c_str() , loadziRecord , p,&errMsg);
	CCLog("getZiDataInfo error code:%d error:%s",ret,errMsg);
	if (errMsg)
	{
		sqlite3_free(errMsg);
	}
}

int loadziR(void * para, int n_column, char ** column_value, char ** column_name){
	((CharacterExtend*)para)->setID(CCInteger::create(atoi(column_value[0])));		//ID
	((CharacterExtend*)para)->setName(ccs(column_value[1]));						//ziName
	((CharacterExtend*)para)->setSEQ(ccs(column_value[2]));							//strokeIDSeq
	CCLog("%s",column_value[2]);
	((CharacterExtend*)para)->setruleLoose(ccs(column_value[3]));						//ruleLoose
	((CharacterExtend*)para)->setRuleTight(ccs(column_value[4]));
	((CharacterExtend*)para)->setXML(ccs(column_value[5]));							//xml
	return 0;
}

void SQLiteHelper::getZiDataInfoExtend(string sql,CCObject* p){
	int ret = sqlite3_exec(pDB, sql.c_str(), loadziR, p ,&errMsg);
	if (errMsg)
	{
		sqlite3_free(errMsg);
	}
}

int getFuncBody(void * para, int n_column, char ** column_value, char ** column_name){
	CCLog("getFuncBody");
	((strokeFunc*)para)->setFunc(ccs(column_value[2]));
	return 0;
}

void SQLiteHelper::getstrokeFunc(string sql,CCObject* funcbody){
	int ret = sqlite3_exec(pDB,sql.c_str(),getFuncBody,funcbody,&errMsg);
	CCLog("SqliteHelper::getstrokeFunc error code:%d error:%s",ret,errMsg);

}

int groupCharacterCallback(void * para, int n_column, char ** column_value, char ** column_name){
	vector<string>* result = (vector<string>*)para;
	for (int i=1; i < 17; i++)
	{
		result->push_back(column_value[i]);
	}
	return 0;
}

vector<string> SQLiteHelper::getGroupCharacter(string sql){
	vector<string> result;
	int ret = sqlite3_exec(pDB, sql.c_str(), groupCharacterCallback, &result, &errMsg);
	if (errMsg)
	{
		CCLog("return getDataInfo error code:%d error:%s",ret,errMsg);
		sqlite3_free(errMsg);
	}
	return result;
}

int getUnitCallback(void* para, int n_column, char** column_value, char** column_name){
	string* result = (string*)para;
	if (strcmp(column_name[2],"characters")==0)
	{
		result->append(column_value[2]);
	}
	return 0;
}

string SQLiteHelper::getUnit(string sql){
	string result;
	int ret = sqlite3_exec(pDB, sql.c_str(), getUnitCallback, &result, &errMsg);
	if (errMsg)
	{
		CCLog("return getUnit error code:%d error:%s",ret,errMsg);
		sqlite3_free(errMsg);
	}
	return result;
}

int getIDs(void* para, int n_column, char** column_value, char** column_name){
	vector<string>* ret = (vector<string>*)para;
	ret->push_back(column_value[0]);
	return 0;
}

vector<string> SQLiteHelper::getUnitIDs(string sql){
	vector<string> result;
	int ret = sqlite3_exec(pDB, sql.c_str(), getIDs, &result, &errMsg);
	if (errMsg)
	{
		CCLog("getUnitIDs error code:%d error:%s",ret,errMsg);
		sqlite3_free(errMsg);
	}
	return result;
}

int getNotes(void* para, int n_column, char** column_value, char** column_name){
	vector<vector <string> >* ret = (vector< vector <string> >*) para;
	vector<string> temp;
	if (strcmp(column_name[3],"note") == 0)
	{
		//�����������note
		temp.push_back(column_value[0]);
		temp.push_back(column_value[3]);
	}
	ret->push_back(temp);
	return 0;
}

vector<vector <string> > SQLiteHelper::getNote(string sql){
	vector<vector <string> > result;
	int ret = sqlite3_exec(pDB, sql.c_str(), getNotes, &result, &errMsg);
	if (errMsg)
	{
		CCLog("getNote error code: %d error: %s",ret, errMsg);
		sqlite3_free(errMsg);
	}
	return result;
}

void SQLiteHelper::closeDB()
{
	result = sqlite3_close(pDB); 
	if (result == SQLITE_OK)
	{
		CCLog("close database succeed");
	}else
	{
		CCLog("close database failed");
	}
}
