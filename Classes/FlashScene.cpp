#include "FlashScene.h"
#include "LoadingScene.h"
#include "Constants.h"

CCScene* FlashScene::scene()
{
	CCScene *scene = CCScene::create();
	FlashScene *layer = FlashScene::create();
	scene->addChild(layer);
	return scene;
}

bool FlashScene::init()
{
	if (!CCLayer::init())
		return false;

	CCLayerColor *bg = CCLayerColor::create(ccc4(255, 255, 255, 255), WINSIZE.width, WINSIZE.height);
	bg->setPosition(0, 0);
	this->addChild(bg);

	CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
	const char *s = str->valueForKey("title")->m_sString.c_str();
	CCLabelTTF *title = CCLabelTTF::create(s, "", 50);
	title->setColor(ccc3(43, 113, 255));
	title->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2 + 100));
	this->addChild(title, 2);
	
	CCSprite *qqSprite = CCSprite::create("qq.png");
	qqSprite->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));
	this->addChild(qqSprite);

	this->scheduleOnce(schedule_selector(FlashScene::startLoadingScene), 2.0f);

	return true;
}

void FlashScene::startLoadingScene(float dt)
{
	CCTransitionFade *trans = CCTransitionFade::create(0.5, LoadingScene::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}