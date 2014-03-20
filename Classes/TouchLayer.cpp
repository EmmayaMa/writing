#include "TouchLayer.h"

TouchLayer::TouchLayer()
{
}

TouchLayer::~TouchLayer()
{
}

bool TouchLayer::init(TcharacterLayer* t,HcharacterLayer* h){
	CCLog("TouchLayer init()");
	if (CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		this->isOutside = false;
		this->isStartOutside = false;
		this->Tlayer = t;
		this->Hlayer = h;
		this->setTouchEnabled(true);
		this->setOpacity(0);			//ȫ͸��
		CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);	//register touch event


		return true;
	}
	return false;
}

TouchLayer* TouchLayer::create(TcharacterLayer* t,HcharacterLayer* h){
	TouchLayer* pRet = new TouchLayer();
	if (pRet && pRet->init(t,h))
	{
		pRet->autorelease();
		return pRet;
	}else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void TouchLayer::onEnter(){

}
void TouchLayer::onExit(){

}
void TouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	CCLog("TouchLayer TouchesBegan");
	CCPoint touchpoint = ((CCTouch*)pTouches->anyObject())->getLocationInView();
	touchpoint = CCDirector::sharedDirector()->convertToUI(touchpoint);
	//CCLog("x= %f, y= %f",touchpoint.x,touchpoint.y);
	CCSprite* tianzige = Hlayer->getSprite();
	if (tianzige->boundingBox().containsPoint(touchpoint))
	{
		//�ڷ�Χ��
		points.push_back(touchpoint);
		Stroke str(points);
		Hlayer->m_HDrawnode->addStroke(str);
	}else
	{
		//���ڷ�Χ��
		this->isStartOutside = true;
		points.clear();
	}
	//CCLog("isStartOutside = %d, isOutside = %d",isStartOutside,isOutside);
// 	HcharacterDrawnode* t= Hlayer->m_HDrawnode;
	
}
void TouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	CCLog("TouchLayer TouchesMoved");
	CCPoint touchp = ((CCTouch*)pTouches->anyObject())->getLocationInView();
	touchp = CCDirector::sharedDirector()->convertToUI(touchp);
	//CCLog("x= %f, y= %f",touchp.x,touchp.y);

	CCSprite* tianzige = Hlayer->getSprite();
	if (isStartOutside)
	{
		return;
	}
	if (tianzige->boundingBox().containsPoint(touchp))
	{
		//�ڷ�Χ�ڣ���������ڷ�Χ��
		points.push_back(touchp);
		Hlayer->m_HDrawnode->addPoint(touchp);
	}else if(!tianzige->boundingBox().containsPoint(touchp))
	{
		//���ٷ�Χ�ڣ���������ڷ�Χ��
		isOutside = true;
	}
	//CCLog("x= %f, y= %f",touchp.x,touchp.y);
	//CCLog("isStartOutside = %d, isOutside = %d",isStartOutside,isOutside);
}
void TouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	CCLog("TouchLayer TouchesEnded");
	CCPoint touchp = ((CCTouch*)pTouches->anyObject())->getLocationInView();
	touchp = CCDirector::sharedDirector()->convertToUI(touchp);
	CCSprite* tianzige = Hlayer->getSprite();
	if (isStartOutside)
	{
		isStartOutside = false;
		isOutside = false;
		points.clear();
		return;
	}
	if (tianzige->boundingBox().containsPoint(touchp) && isOutside == false)
	{
		//�ڷ�Χ�ڣ���������ڷ�Χ��,��;û�г����ָ�
		points.push_back(touchp);
		Hlayer->m_HDrawnode->addPoint(touchp);

		//һ����ɣ�������㣬��;��β�㶼�ڷ�Χ�ڣ������ݱ�����points��
		Hlayer->judge();			//�Զ���HcharacterDrawnode�л�ȡ����Ϣ


		points.clear();
	}else if (!tianzige->boundingBox().containsPoint(touchp) && isOutside == false)
	{
		//���ڷ�Χ�ڣ���;û�����ָ�
		Hlayer->m_HDrawnode->removeLastStroke();
	}else if(isOutside == true)
	{
		Hlayer->m_HDrawnode->removeLastStroke();
		isOutside = false;
	}
	//CCLog("x= %f, y= %f",touchp.x,touchp.y);
	//CCLog("isStartOutside = %d, isOutside = %d",isStartOutside,isOutside);
	isStartOutside = false;
	isOutside = false;
	points.clear();
}
void TouchLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}