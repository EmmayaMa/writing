
#include "GameScene.h"
#include "GameOverScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
GameScene::GameScene():_targets(NULL),_projectiles(NULL),_projectilesDestroyed(0)
{
    _targets = new CCArray();
    _projectiles = new CCArray();
}

GameScene::~GameScene(void)
{
    CC_SAFE_RELEASE_NULL(_targets);
    CC_SAFE_RELEASE_NULL(_projectiles);
}

CCScene* GameScene::scene()
{
    CCScene * scene = CCScene::create();
    GameScene * layer = GameScene::create();

    scene->addChild(layer);
    return scene;
}

bool GameScene::init(){
    if( CCLayerColor::initWithColor(ccc4(255,255,255,255)) ){
	this->setTouchEnabled(true);
	this->schedule( schedule_selector(GameScene::gameLogic ) , 1.0);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite * player = CCSprite::create( "Player.png" , CCRectMake(0,0,27,40) );

	player->setPosition( ccp(player->getContentSize().width/2 , winSize.height/2 ) );
	this->addChild(player);

	this->scheduleUpdate();
	return true;
    }
    return false;
}

void GameScene::addTarget(){
    CCSprite * target = CCSprite::create(  "Target.png" , CCRectMake(0,0,27,40) );

    //����������ֵ�XY����
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minY = target->getContentSize().height/2;
    int maxY = winSize.height - target->getContentSize().height/2;
    int rangeY = maxY-minY;
    int actualY = (rand() % rangeY)+minY;

    // ���������ʱ��������΢��һЩ��Ļ
    // �������λ�õ�Y�����������
    target->setPosition( 
	ccp(winSize.width + (target->getContentSize().width/2), 
	actualY) );
    this->addChild(target);

    // ͨ���趨�����˶�����ʱ�������������ٶ�
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    // srand( TimGetTicks() );
    int actualDuration = ( rand() % rangeDuration )  + minDuration;

    // ����action
    CCFiniteTimeAction* actionMove = 
	CCMoveTo::create( (float)actualDuration, 
	ccp(0 - target->getContentSize().width/2, actualY) );
    CCFiniteTimeAction* actionMoveDone =   CCCallFuncN::create( this, callfuncN_selector(GameScene::spriteMoveFinished));
    target->runAction( CCSequence::create(actionMove, 
	actionMoveDone, NULL) );

    target->setTag(1);
    _targets->addObject(target);

}


void GameScene::spriteMoveFinished(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
    // �� tag �ж����ʹӶ�Ӧ���������Ƴ�
    if (sprite->getTag() == 1)  
    {
	_targets->removeObject(sprite);
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
	CCDirector::sharedDirector()->replaceScene(gameOverScene);    
    }
    else if (sprite->getTag() == 2) 
    {
	_projectiles->removeObject(sprite);
    }
}

void GameScene::gameLogic(float dt)
{
    this->addTarget();
}

void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCLog("Game Scene TouchedEnded ... ");
    // �Ӵ�����ļ�����ѡȡһ����
    
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocation();

    // ��ʼ����ķ��ڲ����趨һ�����
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *projectile = CCSprite::create("Projectile.png", CCRectMake(0, 0, 20, 20));
    projectile->setPosition( ccp(20, winSize.height/2) );

    // �������·��������������Ǵ������X��Y�����ƫ����
    int offX = location.x - projectile->getPosition().x;
    int offY = location.y - projectile->getPosition().y;

    // ����Ҫ�������ֵĵط��򡭡����������������ǲ��ų���
    /* ���õ�������return��֮ǰcreate�ķ���û���ͷŻ����
    �ڴ�й©��ʹ��create���������Ķ������Զ��ͷŵģ�
    �����������ֶ��ĵ��������� retain() ������*/
    if (offX <= 0) return;

    // ��Ȼ���������ִ���ô�Ͱ����ӵ���Ϸ����ȥ
    this->addChild(projectile);

    // ����һ�·������յ�Ŀ�ĵأ�����ϣ�����ɳ���Ļ����ʧ
    int realX = winSize.width
	+ (projectile->getContentSize().width/2);
    float ratio = (float)offY / (float)offX;
    int realY = (realX * ratio) + projectile->getPosition().y;
    CCPoint realDest = ccp(realX, realY);

    // ����һ�·���Ҫ�ɶ�Զ����Ϊ�ٶ�����ͬ�ģ�Ҫ����������ʱ�䡣
    int offRealX = realX - projectile->getPosition().x;
    int offRealY = realY - projectile->getPosition().y;
    float length = sqrtf((offRealX * offRealX) 
	+ (offRealY*offRealY));
    float velocity = 480/1; // 480 �ٶ��� pixel/ 1 second 
    float realMoveDuration = length/velocity;

    // ��MoveTO�����÷�����ͬ�����ٶȷɵ���ͬ��Ŀ�ĵأ�ͬ��ִ�н���
    // ֮���õ��� spriteMoveFinished ������
    projectile->runAction( CCSequence::create(
	CCMoveTo::create(realMoveDuration, realDest),
	CCCallFuncN::create(this, 
	callfuncN_selector(GameScene::spriteMoveFinished)), 
	NULL) );

    projectile->setTag(2);
    _projectiles->addObject(projectile);
}


void GameScene::update(float dt)
{
    CCArray* projectilesToDelete = new CCArray();
    CCObject* pobject;

    // cocos2d����ĺ꣬�ṩ�����ֻ������CCARRAYд��
    CCARRAY_FOREACH(_projectiles, pobject)
    {
	CCSprite* projectile = (CCSprite*)pobject;
	CCRect pRect = CCRect(projectile->getPosition().x - projectile->getContentSize().width/2, 
	    projectile->getPosition().y - projectile->getContentSize().height/2, 
	    projectile->getContentSize().width, 
	    projectile->getContentSize().height);     

	CCArray* targetsToDelete = new CCArray();
	CCObject* tobject;
	CCARRAY_FOREACH(_targets, tobject)
	{
	    CCSprite* target = (CCSprite*)tobject;
	    CCRect tRect = CCRect(target->getPosition().x - target->getContentSize().width/2, 
		target->getPosition().y - target->getContentSize().height/2, 
		target->getContentSize().width, 
		target->getContentSize().height);

	    // ��ײ����
	    if( pRect.intersectsRect( tRect ) )
	    {
		targetsToDelete->addObject( target );
		// �����ɵ��������������������30����ת����Ϸ��������
		_projectilesDestroyed++;                       
		if (_projectilesDestroyed > 30)
		{
		    GameOverScene *gameOverScene = GameOverScene::create();
		    gameOverScene->getLayer()->getLabel()->setString("You Win!");
		    CCDirector::sharedDirector()->replaceScene(gameOverScene);
		}
	    }
	}

	// �Ƴ������е�Ŀ��
	CCARRAY_FOREACH(targetsToDelete, tobject)
	{
	    CCSprite* target = (CCSprite*)tobject;
	    _targets->removeObject(target);
	    this->removeChild(target, true);
	}

	// ��¼����Ŀ����ӵ�
	if(targetsToDelete->count() > 0)
	{
	    targetsToDelete->addObject(projectile);
	}

	/* �����������õ� new CCArray() ���� CCArray::create()
	��õ��������������Ҫ�ֶ�����release */
	targetsToDelete->release();
    }

    // �Ƴ�����Ŀ����ӵ�
    CCARRAY_FOREACH(projectilesToDelete, pobject)
    {
	CCSprite* projectile = (CCSprite*)pobject;
	_projectiles->removeObject(projectile, true);
	this->removeChild(projectile, true);
    }

    projectilesToDelete->release();
}    

void GameScene::keyBackClicked(){
    //��Ϸ�������˰�ť
    CCLog("GameScene back key pressed...");
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());

}
