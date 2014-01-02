#include "StrokeNode.h"
#include "Stroke.h"
// #include "CCDrawingPrimitives.h"

USING_NS_CC;

StrokeNode::StrokeNode(Stroke stroke)
{
	n_stroke = stroke;
	//����CCNode��С
	CCPoint p = n_stroke.getBigPoint();
	this->setContentSize(CCSizeMake(p.x,p.y));

	//��ӽڵ�,���� ��draw������ 
	

}


StrokeNode::~StrokeNode(void)
{
}

bool StrokeNode::init(){



	return true;
}

void StrokeNode::draw(void){
// 	ccDrawLine(CCPointZero,CCPointMake(100,100));
	
	glLineWidth( 5.0f );//�����߿�
	ccDrawColor4B(255,0,0,255);//�����ߵ���ɫ
	//�����㣬�����߶�
	CCPoint tmp = n_stroke.pointList[0];
	for (int i = 0 ; i < n_stroke.pointList.size() ; ++i)
	{
		ccDrawLine(tmp,n_stroke.pointList[i]);
		tmp = n_stroke.pointList[i];
	}
	CCSize tmpSize = getContentSize();

	//�����ĵ�
	ccPointSize(4);
	ccDrawColor4B(0,255,255,255);

	ccDrawPoint(n_stroke.getMidPoint());
	ccDrawPoint(CCPointZero);
}


StrokeNode* StrokeNode::getStrokeNode(Stroke stroke){


	StrokeNode* node = new StrokeNode(stroke);
	if (node && node->init())
	{
		node->autorelease();
		return node;
	}
	CC_SAFE_DELETE(node);
	return NULL;
}

CCPoint StrokeNode::getMidStrokePoint(){
	return n_stroke.getMidPoint();
}

//���������õ��ʻ������ģ�����������û�ȥ
void StrokeNode::setAnchorMidStroke(){
	CCPoint midp = n_stroke.getMidPoint();
	CCPoint p = n_stroke.getBigPoint();
	float ax = p.x/midp.x;
	float ay = p.y/midp.y;
	this->setAnchorPoint(ccp(ax,ay));
}