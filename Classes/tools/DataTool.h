#ifndef _DataTool_H_
#define _DataTool_H_

#pragma once
#include "cocos2d.h"
#include <iostream>
#include <string>
USING_NS_CC;
using namespace std;

class DataTool
{
public:
//	static string GB2312ToUTF8(string strGBK);
//	static string GBKToUTF8(string gbk);
	//��intת��string�ַ���
	static string intTostring(int a);
	/**
		���ַ������浽�ļ���
	*/

	static string floatToString(float f);

	static float stringToFloat(string str);

	static void storeToFile(const char* str,char* filename);
	/**
		���ļ��ж�ȡ�ַ���
	*/
	static string readFromFile(char* filename);

	/**
	 * ��ȡ�����ַ�
	 * @param key �����ַ�����key value������xml��
	 * @return
	 */
	static string getChinese(string key);
};
#endif
