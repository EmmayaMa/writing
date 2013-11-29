#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "SecondScene.h"
#include "TestMoveSprite.h"
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#include "Lua_extensions_CCB.h"
#include "Lua_web_socket.h"
#include "HclcData.h"
//#include "sqlite3.h"
#include "GameWall.h"
#include "PopLayer.h"

//#define COCOS2D_DEBUG 1
using namespace std;
USING_NS_CC;
HelloWorld::~HelloWorld()
{
	//cocos2d����ĺ꣬���ȼ������´���
	//if (_targets)
	//{
	//  _targets->release();
	//  _targets = NULL;
	//}
	//CC_SAFE_RELEASE_NULL(_targets);
	//CC_SAFE_RELEASE_NULL(_projectiles);

	// �ǵð�������������Ϊ�麯��
}

HelloWorld::HelloWorld()
{

}    

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	CCLog("HelloWorld init...");
	//sqlite_test();
	if (!CCLayerColor::initWithColor(ccc4(218,112,214,255)) )
	{
		return false;
	}

	if (!this->isTouchEnabled())
	{
		this->setTouchEnabled(true);
	}

	
	// ÿ����� HellowWorld::gameLogic ����һ��
	//this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );

	//returns the size of the OpenGL view in points.
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	/*
	CCSprite* player = CCSprite::create("Player.png", CCRectMake(0, 0, 27, 40));
	player->setPosition( ccp(player->getContentSize().width/2, 
	winSize.height/2) );
	this->addChild(player);
	*/

	//returns visible size of the OpenGL view in points.
	//the value is equal to getWinSize if don't invoke CCEGLView::setDesignResolutionSize()
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//returns visible origin of the OpenGL view in points.
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	// add a "close" icon to exit the progress. it's an autorelease object

	//create MenuItem that start the first Game
	CCMenuItemImage *pStartItem = CCMenuItemImage::create(
		"Button1.png",
		"Button1Sel.png",
		this,
		menu_selector(HelloWorld::menuStartGame));

	pStartItem->setPosition(ccp(origin.x + visibleSize.width/2 ,
		origin.y + visibleSize.height/2 + pStartItem->getContentSize().height/2 ));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pStartItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);

	//create menu start second scene draw
	CCMenuItemImage *pSecondItem = CCMenuItemImage::create(
		"Button2.png",
		"Button2Sel.png",
		this,
		menu_selector(HelloWorld::menuSecondScene)
		);
	pSecondItem->setPosition(  ccp(origin.x + visibleSize.width/2 , 
		origin.y + visibleSize.height/2 - pSecondItem->getContentSize().height/2 ) );
	CCMenu* pSecondMenu = CCMenu::create(pSecondItem,NULL);
	pSecondMenu->setPosition(CCPointZero);
	this->addChild(pSecondMenu,1);

	//create button to enter TestMoveSprite
	CCMenuItemImage *pTestMove = CCMenuItemImage::create(
		"Button3.png",
		"Button3Sel.png",
		this,
		menu_selector(HelloWorld::menuTestMoveScene));
	pTestMove->setPosition( ccp(origin.x + visibleSize.width/2 , 
		origin.y + visibleSize.height/2 - 2*pSecondItem->getContentSize().height  ) );
	CCMenu * pTestmoveMenu = CCMenu::create(pTestMove,NULL);
	pTestmoveMenu->setPosition(CCPointZero);
	this->addChild(pTestmoveMenu,1);



	CCMenuItemImage* pMap = CCMenuItemImage::create(
		"Button1.png",
		"button1Sel.png",
		this,
		menu_selector(HelloWorld::menuGameWallScene));
	pMap->setPosition(ccp(origin.x+pMap->getContentSize().width/2,origin.y+pMap->getContentSize().height/2));
	CCMenu* pGameWall = CCMenu::create(pMap,NULL);
	pGameWall->setPosition(CCPointZero);
	this->addChild(pGameWall,1);

	//want to add a button 
	/*
	CCMenuItemImage * testButton = CCMenuItemImage::create("Buttion1.png","Button1Sel.png",this,
	menu_selector(HelloWorld::menuCloseCallback));
	testButton->setPosition( ccp( CCDirector::sharedDirector()->getWinSize().width  - 50 , 50 ) );
	CCMenu * pMenu = CCMenu::create(testButton,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);
	*/

	// add a label shows "Hello World"
	// create and initialize a label

	CCLabelTTF* pLabel = CCLabelTTF::create("Hello World!!", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel,1);


	//     const char* labelstring = this->getStringFromLua();
	//     CCLabelTTF* luaLabel = CCLabelTTF::create(labelstring,"Arial",18);
	//     luaLabel->setPosition(ccp(origin.x + luaLabel->getContentSize().width/2 + 10,
	// 	origin.y + visibleSize.height - luaLabel->getContentSize().height));
	//     this->addChild(luaLabel,1);


	this->scheduleUpdate();
	return true;

	/*
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
	return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	this,
	menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
	origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	CCLabelTTF* pLabel = CCLabelTTF::create("Hello World!!", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	return true;
	*/
}


void HelloWorld::draw(){
	CCLayerColor::draw();
	CCSize size =  CCDirector::sharedDirector()->getWinSize();
	//    glEnable(GL_LINE_SMOOTH);
	ccDrawLine( CCPointMake(0,size.height/2) , CCPointMake(size.width,size.height/2));
	ccDrawLine( CCPointMake(size.width/2 , 0) , CCPointMake(size.width/2 , size.height ));
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	//Menu Close �رյ�ǰ
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuStartGame(CCObject* pSender){
	//GameScene *gameScene = GameScene::create();
	//	GameOverScene * gameOverScene = GameOverScene::create();
	//	gameScene->getLayer()->getLabel()->setString("You Win!");
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void HelloWorld::menuSecondScene(CCObject* pSender){
	//Enter SecondScene
	CCDirector::sharedDirector()->replaceScene(SecondScene::scene());
}


void HelloWorld::keyBackClicked(){
	//when back key pressed , finish the app
	CCDirector::sharedDirector()->end();
}

void HelloWorld::menuTestMoveScene(CCObject * pSender)
{
	CCDirector::sharedDirector()->replaceScene(TestMoveSprite::scene());
}

void HelloWorld::menuGameWallScene(CCObject* pSender){
	CCDirector::sharedDirector()->replaceScene(GameWall::scene());
}

const char* HelloWorld::getStringFromLua(){

	//http://1901.github.io/2013/01/05/lua_in_cocos2d-x.html
	//ע��LUA�ű�����
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

	//ִ��һ��LUA�ַ���
	//pEngine->executeString("print(\"test executeString\\n\")");

	//ִ��һ��LUA�ļ�
	std::string filepath = CCFileUtils::sharedFileUtils()->fullPathForFilename("test.lua");
	const char* pfilepath = filepath.c_str();
	pEngine->executeScriptFile(pfilepath);

	//ִ��LUA�е�һ��ȫ�ַ���
	//pEngine->executeGlobalFunction("testfunc");

	//http://www.himigame.com/lua-game/1343.html
	CCLOG("Str = %s",HclcData::sharedHD()->getLuaVarString("Test.lua","luaStr"));
	CCLOG("Str2 = %s",HclcData::sharedHD()->getLuaVarString("Test.lua","luaStr2"));
	CCLOG("age = %s",HclcData::sharedHD()->getLuaVarOneOfTable("Test.lua", "luaTable","age"));
	CCLOG("name = %s",HclcData::sharedHD()->getLuaVarOneOfTable("Test.lua", "luaTable","name"));
	CCLOG("sex = %s",HclcData::sharedHD()->getLuaVarOneOfTable("Test.lua", "luaTable","sex"));
	string re = HclcData::sharedHD()->getLuaVarTable("Test.lua", "luaTable");
	//    CCLOG("Table = %s",);
	//    CCLOG("Call Lua Function Back: %s",HclcData::sharedHD()->callLuaFunction("Test.lua", "luaLogString"));

	//    HclcData::sharedHD()->callCppFunction("Test.lua");
	//    HclcData::sharedHD()->callLuaFunction("Test.lua", "call_Cpp");
	return HclcData::sharedHD()->getLuaVarString("Test.lua","luaStr");
}

/*
void HelloWorld::sqlite_test(){
std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("test.db");
sqlite3* pSqlite = NULL;
int result = sqlite3_open(filename.c_str(),&pSqlite);
CCLog(filename.c_str());  
if( result != SQLITE_OK )  
CCLog( "�����ݿ�ʧ�ܣ�������:%d ������ԭ��:\n" , result );  
else  
CCLog("�ɹ��ش������ݿ�");  

}*/

/*
void HelloWorld::addTarget(){
CCSprite * target = CCSprite::create("Target.png", CCRectMake(0,0,27,40) );

//����������ֵ�XY����
CCSize winSize = CCDirector::sharedDirector()->getWinSize();
int minY = target->getContentSize().height/2;
int maxY = winSize.height - target->getContentSize().height/2;
int rangeY = maxY-minY;
int actualY = (rand() % rangeY)+minY;

// ���������ʱ��������΢��һЩ��Ļ
//�������λ�õ�Y�����������
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
CCFiniteTimeAction* actionMoveDone =   CCCallFuncN::create( this, callfuncN_selector(HelloWorld::spriteMoveFinished));
target->runAction( CCSequence::create(actionMove, 
actionMoveDone, NULL) );

target->setTag(1);
_targets->addObject(target);
}


void HelloWorld::spriteMoveFinished(CCNode* sender)
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

void HelloWorld::gameLogic(float dt)
{
this->addTarget();
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
CCLOG("TTT");
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
�����������ֶ��ĵ��������� retain() ������
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
callfuncN_selector(HelloWorld::spriteMoveFinished)), 
NULL) );

projectile->setTag(2);
_projectiles->addObject(projectile);
}


void HelloWorld::update(float dt)
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

//�����������õ� new CCArray() ���� CCArray::create()��õ��������������Ҫ�ֶ�����release
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
*/


void HelloWorld::popup(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PopLayer* popL = PopLayer::create("pop/background.png");
	popL->setContentSize(CCSizeMake(400,400));
	popL->setTitle("test");
	popL->setCallBackFunc(this,callfuncN_selector(HelloWorld::buttonCallBack));
	popL->addButton("Button1.png","Button1.png","Y",0);
	popL->addButton("Button2.png","Button2.png","N",1);
	this->addChild(popL,100);
}

void HelloWorld::buttonCallBack(CCNode* pSender){
	CCLog("button call back. tag: %d", pSender->getTag());

}