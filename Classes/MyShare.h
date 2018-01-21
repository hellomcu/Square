#ifndef __MYSHARE_H__
#define __MYSHARE_H__

#include "cocos2d.h"
#include <string>

using namespace std;

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "Common/CCUMSocialSDK.h"

//  π”√”—√À√¸¡Óø’º‰
USING_NS_UM_SOCIAL;

#endif

class MyShare : public CCObject
{
public:
	static MyShare * getMyShare();

	void share(const char* content);

	virtual void shareCallback(int platform, int stCode, string& errorMsg);

	MyShare();
	~MyShare();
private:
	void saveScreenShot();
	
};

#endif

