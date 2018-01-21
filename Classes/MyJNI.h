#ifndef __MYJNI_H__
#define __MYJNI_H__

#include "cocos2d.h"

USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"

class MyJNI : public CCObject
{
public:
	static MyJNI *sharedJNI();

	void showInterstitialAd();
	void cancelInterstitialAd();
	void showAppWall();

	MyJNI();
	~MyJNI();
private:
	
	
};

#endif

#endif