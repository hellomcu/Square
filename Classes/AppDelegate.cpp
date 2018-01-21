#include "AppDelegate.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "FlashScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MobClickCpp.h"
#endif

using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	MOBCLICKCPP_START_WITH_APPKEY("53daeb76fd98c555780154ed");
	#endif

    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize(480, 800, kResolutionShowAll);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("ready_bg.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("game_bg.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("over.wav");
	// turn on display FPS
	//pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = FlashScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::applicationDidEnterBackground();
	#endif

	//CCDirector::sharedDirector()->pause();
    CCDirector::sharedDirector()->stopAnimation();
    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	
	GameScene *scene = (GameScene *)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1);
	if (scene && scene->gameIsStart)
	{
		scene->gameOver();	
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::applicationWillEnterForeground();
	#endif

	//CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
