#ifndef __LuaScriptReader_H__
#define __LuaScriptReader_H__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LUASCRIPTREADER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LUASCRIPTREADER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#include <string>
using namespace std;

extern "C"{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#define MAX_LUA_FILE_LEN 1024*20
// This class is exported from the LuaScriptReader.dll
class  CLuaScriptReader {
public:
	CLuaScriptReader(void);
	~CLuaScriptReader();
protected:
	lua_State *m_plua;
	string sourcecode;
public:
	bool InitLuaScriptReader();	//��ʼ��lua��lua�ĵײ��
	void ExitLuaScriptReader();	//�ͷ�lua
	bool RunScriptBuffer(const char *buff,char *name);	//����buff�е�lua����,��������ֵ
	bool RunScriptBuffer(const char *buff,char* ret_string,char *name); //����buff��lua���룬������ֵ
	bool RunScriptFile(const char *filename,char *name);//����buff��lua�ļ�
	bool RunScriptFile(const char *filename,char* ret_string,char *name);//����buff��lua�ļ�,������ֵ	
	bool GetSourceCode(char *sourcecode);
	bool SetWriteZiInfo(const char *wz);
	bool GetStandardZiInfo(char stdinfo[]);
	bool GetRunType(int level, int step);
	bool GetUnitIndex(int idx);
	bool GetStrokeIndex(int idx);
	bool GetGlobalFunc(char *globalfunc);
	void SetGlobalFunc(const char * filename);	//
	void SetRulesFunc(const char* filename);
	bool RunMixedFile(const char *filename,char *name);
	bool Print2File(char* buff,char*file);

	void SetZiName(string hanzi);
};


#endif
