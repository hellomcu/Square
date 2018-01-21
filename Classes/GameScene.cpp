#include "GameScene.h"
#include "Constants.h"
#include "MySquare.h"
#include "SimpleAudioEngine.h"
#include "LoadingScene.h"
#include "Math.h"
#include "OverDialog.h"

using namespace CocosDenshion;

CCScene * GameScene::scene()
{
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create();
	layer->setTag(1);
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	gameIsStart = false;
	speed = 500;
	createWorld();
	initPoint();
	//创建墙体
	createWall();
	createOtherSquare();
	createMySquare();
	audioIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey("audio", true);
	if (audioIsOpen)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("ready_bg.mp3", true);
	}

	return true;
}

void GameScene::createWorld()
{
	world = new b2World(b2Vec2(0, 0));
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	world->SetContactListener(this);
}

void GameScene::initPoint()
{
	left_top = ccp(WALL_WIDTH, WINSIZE.height - WALL_WIDTH);
	right_top = ccp(WINSIZE.width - WALL_WIDTH, WINSIZE.height - WALL_WIDTH);
	right_bottom = ccp(WINSIZE.width - WALL_WIDTH, WALL_WIDTH);
	left_bottom = ccp(WALL_WIDTH, WALL_WIDTH);
}

void GameScene::createMySquare()
{
	mySquare = MySquare::create(ccc4(255, 0, 128, 255), 50, 50);
	mySquare->setScene(this);
	CCSize s = mySquare->getContentSize();
	mySquare->ignoreAnchorPointForPosition(false);	//不忽略锚点
	mySquare->setAnchorPoint(ccp(0.5f, 0.5f));
	mySquare->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));
	mySquare->createBody(world);
	this->addChild(mySquare);
}

void GameScene::createWall()
{
	topWall = CCLayerColor::create(ccc4(127, 127, 127, 255), WALL_LENGTH, WALL_SIZE);
	topWall->setPosition(ccp(0, WINSIZE.height - WALL_WIDTH));
	this->addChild(topWall);

	bottomWall = CCLayerColor::create(ccc4(127, 127, 127, 255), WALL_LENGTH, WALL_SIZE);
	bottomWall->setPosition(ccp(0, WALL_WIDTH - WALL_SIZE));
	this->addChild(bottomWall);

	leftWall = CCLayerColor::create(ccc4(127, 127, 127, 255), WALL_SIZE, WALL_HEIGHT);
	leftWall->setPosition(ccp(WALL_WIDTH - WALL_SIZE, 0));
	this->addChild(leftWall);

	rightWall = CCLayerColor::create(ccc4(127, 127, 127, 255), WALL_SIZE, WALL_HEIGHT);
	rightWall->setPosition(ccp(WINSIZE.width - WALL_WIDTH, 0));
	this->addChild(rightWall);

	b2BodyDef wallBodyDef;
	wallBodyDef.type = b2_staticBody;
	wallBodyDef.position.Set(0, 0);
	b2Body *wallBody = world->CreateBody(&wallBodyDef);
	b2EdgeShape wallShape;
	wallShape.Set(b2Vec2(left_top.x / RATIO, left_top.y / RATIO), b2Vec2(right_top.x / RATIO, right_top.y / RATIO));
	wallBody->CreateFixture(&wallShape, 0);
	wallShape.Set(b2Vec2(right_top.x / RATIO, right_top.y / RATIO), b2Vec2(right_bottom.x / RATIO, right_bottom.y / RATIO));
	wallBody->CreateFixture(&wallShape, 0);
	wallShape.Set(b2Vec2(left_bottom.x / RATIO, left_bottom.y / RATIO), b2Vec2(right_bottom.x / RATIO, right_bottom.y / RATIO));
	wallBody->CreateFixture(&wallShape, 0);
	wallShape.Set(b2Vec2(left_top.x / RATIO, left_top.y / RATIO), b2Vec2(left_bottom.x / RATIO, left_bottom.y / RATIO));
	b2Fixture *fixtrue = wallBody->CreateFixture(&wallShape, 0);
	fixtrue->SetFriction(0.0f);
}

void GameScene::createOtherSquare()
{
	square1 = Square::create(ccc4(0, 162, 232, 255), 80, 80);
	square1->ignoreAnchorPointForPosition(false);	//不忽略锚点
	square1->setAnchorPoint(ccp(0.5f, 0.5f));
	square1->setPosition(ccp(100, WINSIZE.height - 80));
	square1->createBody(world);
	this->addChild(square1);

	square2 = Square::create(ccc4(0, 162, 232, 255), 100, 80);
	square2->ignoreAnchorPointForPosition(false);	//不忽略锚点
	square2->setAnchorPoint(ccp(0.5f, 0.5f));
	square2->setPosition(ccp(WALL_LENGTH - 100, WINSIZE.height - 80));
	square2->createBody(world);
	this->addChild(square2);

	square3 = Square::create(ccc4(0, 162, 232, 255), 70, 100);
	square3->ignoreAnchorPointForPosition(false);	//不忽略锚点
	square3->setAnchorPoint(ccp(0.5f, 0.5f));
	square3->setPosition(ccp(80, WALL_WIDTH + 60));
	square3->createBody(world);
	this->addChild(square3);

	square4 = Square::create(ccc4(0, 162, 232, 255), 120, 80);
	square4->ignoreAnchorPointForPosition(false);	//不忽略锚点
	square4->setAnchorPoint(ccp(0.5f, 0.5f));
	square4->setPosition(ccp(WALL_LENGTH - 100,  WALL_WIDTH + 50));
	square4->createBody(world);
	this->addChild(square4);
}

void GameScene::createTimeLabel()
{
	timeLabel = CCLabelAtlas::create("", "num.png", 24, 32, '.');
	timeLabel->setAnchorPoint(ccp(0.5, 0.5));
	timeLabel->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));
	timeLabel->setColor(ccc3(255, 242, 0));
	timeLabel->setOpacity(180);
	this->addChild(timeLabel);
	struct cc_timeval tp;
	CCTime::gettimeofdayCocos2d(&tp, NULL);
	init_time_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void GameScene::startGame()
{
	gameIsStart = true;
	createTimeLabel();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("ready_bg.mp3");
	if (audioIsOpen)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_bg.mp3", true);
	}
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::changeSpeed), 5.0f);
	square1->getBody()->SetLinearVelocity(b2Vec2(3, -4));
	square2->getBody()->SetLinearVelocity(b2Vec2(-4, -3));
	square3->getBody()->SetLinearVelocity(b2Vec2(3, 4));
	square4->getBody()->SetLinearVelocity(b2Vec2(-4, 3));
}

void GameScene::update(float dt)
{
	world->Step(dt, 8, 1);
	for (b2Body *b=world->GetBodyList(); b; b=b->GetNext())
	{
		
		CCNode * node = (CCNode *)b->GetUserData();
		if (node)
		{
			b2Vec2 vec = b->GetPosition();
			node->setPosition(ccp(vec.x * RATIO, vec.y * RATIO));
		}
	}
	updateTime();
}

void GameScene::BeginContact(b2Contact *contact)
{
	if (contact->GetFixtureA()->GetBody()->GetUserData() == mySquare || 
		contact->GetFixtureB()->GetBody()->GetUserData() == mySquare)
	{
		gameOver();
		//CCLog("gameover!!!");
	}
}

void GameScene::gameOver()
{
	
	gameIsStart = false;
	OverDialog *overDialog = OverDialog::create(ccc4(0, 182, 255, 255), WINSIZE.width - 100, 280, "Gameover");
	overDialog->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));
	this->addChild(overDialog, 5);
	unscheduleAllSelectors();
	if (audioIsOpen)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("over.wav");
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
	float bestTime = CCUserDefault::sharedUserDefault()->getFloatForKey("best_time", 0.0f);
	CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");

	float total_time = atof(timeLabel->getString());

	overDialog->setScore(timeLabel->getString());
	if (total_time <= bestTime)
	{
		overDialog->setContent(timeLabel->getString(), ccc3(255, 255, 255));
	}
	else
	{
		//保存新纪录
		CCUserDefault::sharedUserDefault()->setFloatForKey("best_time", total_time);
		const char *s1 = str->valueForKey("new_record")->m_sString.c_str();
		const char *msg = CCString::createWithFormat("%s%s", s1, timeLabel->getString())->getCString();
		overDialog->setContent(msg, ccc3(255, 0, 0));
	}
	//CCUserDefault::sharedUserDefault()->setFloatForKey("best_time", 0);
	//CCDirector::sharedDirector()->replaceScene(GameScene::scene());
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mySquare);
}

inline void GameScene::updateTime()
{
	struct cc_timeval tp;
	CCTime::gettimeofdayCocos2d(&tp, NULL);
	float curr_time_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	CCString *timeStr = CCString::createWithFormat("%.3f", (curr_time_ms - init_time_ms) / 1000);
	timeLabel->setString(timeStr->getCString());
}

inline void GameScene::changeSpeed(float dt)
{
	b2Vec2 vec = square1->getBody()->GetLinearVelocity();
	vec.x *= SPEED_INCREMENT;
	vec.y *= SPEED_INCREMENT;
	square1->getBody()->SetLinearVelocity(vec);
	vec = square2->getBody()->GetLinearVelocity();
	vec.x *= SPEED_INCREMENT;
	vec.y *= SPEED_INCREMENT;
	square2->getBody()->SetLinearVelocity(vec);
	vec = square3->getBody()->GetLinearVelocity();
	vec.x *= SPEED_INCREMENT;
	vec.y *= SPEED_INCREMENT;
	square3->getBody()->SetLinearVelocity(vec);
	vec = square4->getBody()->GetLinearVelocity();
	vec.x *= SPEED_INCREMENT;
	vec.y *= SPEED_INCREMENT;
	square4->getBody()->SetLinearVelocity(vec);
	if (fabs(vec.x) > 30)
		unschedule(schedule_selector(GameScene::changeSpeed));
}

void GameScene::keyBackClicked()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCTransitionFade *trans = CCTransitionFade::create(0.5, LoadingScene::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void GameScene::onEnterTransitionDidFinish()
{
	setKeypadEnabled(true);
}