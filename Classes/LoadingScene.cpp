#include "LoadingScene.h"
#include "Constants.h"
#include "SimpleAudioEngine.h"
#include "ShareMenuSquare.h"
#include "StartMenuSquare.h"
#include "MoreAppsMenuSquare.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MobClickCpp.h"
#include "MyJNI.h"
#include "MyShare.h"
#endif

using namespace CocosDenshion;


CCScene* LoadingScene::scene()
{
	CCScene *scene = CCScene::create();
	LoadingScene *layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!CCLayer::init())
		return false;
	createMenu();
	
	return true;
}

void LoadingScene::createMenu()
{
	StartMenuSquare *startMenu = StartMenuSquare::create(ccc4(43, 113, 255, 255), WINSIZE.width / 2 - 15, WINSIZE.height / 3 - 13.3f);
	CCSize size = startMenu->getContentSize();
	startMenu->setPosition(ccp(10, WINSIZE.height - 10 - size.height));
	this->addChild(startMenu, 1);

	AudioMenuSquare *audioMenu = AudioMenuSquare::create(ccc4(0, 182, 255, 255), WINSIZE.width / 2 - 15, WINSIZE.height / 3 - 13.3f);
	audioMenu->setPosition(ccp(10, WINSIZE.height - size.height * 2 - 20));
	this->addChild(audioMenu, 1);

	CCLayerColor *bestTimeMenu = CCLayerColor::create(ccc4(0, 182, 255, 255),  WINSIZE.width / 2 - 15, WINSIZE.height / 3 - 13.3f);
	bestTimeMenu->setPosition(ccp(size.width + 20,  WINSIZE.height - 10 - size.height));
	CCLabelTTF *bestTimeLabel = CCLabelTTF::create("0", "", 40);
	CCDictionary * ss = CCDictionary::createWithContentsOfFile("strings.xml");
	const char *record = ss->valueForKey("record")->m_sString.c_str();
	const char *label = CCString::createWithFormat("%s\n%.3f", record, CCUserDefault::sharedUserDefault()->getFloatForKey("best_time", 0.000f))->getCString();
	bestTimeLabel->setString(label);
	bestTimeLabel->setTag(5);
	bestTimeLabel->setPosition(ccp(size.width / 2, size.height / 2));
	bestTimeMenu->addChild(bestTimeLabel);
	this->addChild(bestTimeMenu, 1);

	ShareMenuSquare *shareMenu = ShareMenuSquare::create(ccc4(43, 113, 255, 255), WINSIZE.width / 2 - 15, WINSIZE.height / 3 - 13.3f);
	shareMenu->setPosition(ccp(size.width + 20, WINSIZE.height - size.height * 2 - 20));
	this->addChild(shareMenu, 1);

	CCLayerColor *helpMenu = CCLayerColor::create(ccc4(43, 113, 255, 255),  WINSIZE.width / 2 - 15, WINSIZE.height / 3 - 15);
	size = helpMenu->getContentSize();
	helpMenu->setPosition(ccp(10, 10));
	CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
	const char *s = str->valueForKey("help")->m_sString.c_str();
	CCLabelTTF *helpLabel = CCLabelTTF::create(s, "", 20);
	helpLabel->setPosition(ccp(size.width / 2, size.height / 2));
	helpMenu->addChild(helpLabel);
	this->addChild(helpMenu, 1);

	MoreAppsMenuSquare *moreAppsMenu = MoreAppsMenuSquare::create(ccc4(0, 182, 255, 255), WINSIZE.width / 2 - 15, WINSIZE.height / 3 - 15);
	moreAppsMenu->setPosition(ccp(size.width + 20, 10));
	this->addChild(moreAppsMenu, 1);

}

void LoadingScene::keyBackClicked()
{
	CCNode *node = this->getChildByTag(1);
	if (node)
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate((CCLayer *)node);
		
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("audio", true))
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		node->removeFromParentAndCleanup(true);
		node = NULL;
		CCDirector::sharedDirector()->resume();

		
		return;
	}
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CCDirector::sharedDirector()->pause();
	
	CCLayerColor *exitLayer = CCLayerColor::create();
	exitLayer->initWithColor(ccc4(0, 0, 0, 125));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create("Are u sure exit?", "", 64);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    exitLayer->addChild(label);
    
    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("OK", this, menu_selector(LoadingScene::exitGameCallback));
    okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));
    
    CCMenuItemFont *cancelMenuItem = CCMenuItemFont::create("Cancel", this, menu_selector(LoadingScene::cancelCallback));
    cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));
    
    CCMenu * m_pMenu = CCMenu::create(okMenuItem, cancelMenuItem, NULL);
    m_pMenu->setPosition(CCPointZero);
    exitLayer->addChild(m_pMenu);
	exitLayer->setTag(1);
	this->addChild(exitLayer, 4);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(exitLayer, 128, true);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		MyJNI::sharedJNI()->showInterstitialAd();
		#endif
}

void LoadingScene::exitGameCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	#endif
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::end();
    CCDirector::sharedDirector()->end();
	#endif
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

void LoadingScene::cancelCallback(CCObject* pSender)
{
	if (pSender)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("audio", true))
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		CCNode *p = (CCNode *)pSender;
		CCNode * node = p->getParent()->getParent();

		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate((CCLayer *)node);
		node->removeFromParentAndCleanup(true);
		node = NULL;
		CCDirector::sharedDirector()->resume();

		
	}
}

void LoadingScene::onEnterTransitionDidFinish()
{	
	//CCLayer::onEnterTransitionDidFinish();
	setKeypadEnabled(true);
}