#include "StrokeDrawnode.h"

StrokeDrawnode::StrokeDrawnode()
{
}

//************************************
// Method:    StrokeDrawnode
// FullName:  StrokeDrawnode::StrokeDrawnode
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: Stroke stro ����һ�ʣ�����һ��Node
//************************************
StrokeDrawnode::StrokeDrawnode(Stroke stro){
	this->stroke = stro;
}

StrokeDrawnode::~StrokeDrawnode()
{
}

void StrokeDrawnode::draw(){
	//CCLog("StrokeDrawnode::draw");
	//�������趨�ʻ��Ĵ�ϸ����ɫ�� ����Ҫ�鿴
	glLineWidth(6.0f);					//�ʻ���ϸ
	ccDrawColor4F(0,0,0,1);				//�ʻ���ɫ

	CCPoint pre = stroke.pointList[0];					//ֱ������pointList��һ��ֵ
	for (int i = 1; i< stroke.pointCount; i++)
	{
		ccDrawLine(pre,stroke.pointList[i]);
		pre = stroke.pointList[i];
	}
}