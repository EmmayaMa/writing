
#ifndef _DataTool_H_
#define _DataTool_H_

#pragma once
#include "cocos2d.h"
using namespace std;


class DataTool
{
public:
	DataTool(void);
	~DataTool(void);

//	static string GB2312ToUTF8(string strGBK);
//	static string GBKToUTF8(string gbk);
	//��intת��string�ַ���
	static string intTostring(int a);
	/**
		���ַ������浽�ļ���
	*/
	static void storeToFile(char* str,char* filename);
	/**
		���ļ��ж�ȡ�ַ���
	*/
	static string readFromFile(char* filename);
	/**
		��ȡ�����ַ�
	*/
	static string getChinese(string key);
};
#endif
