#include "MyJNI.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

MyJNI *instance = NULL;

MyJNI::MyJNI()
{
	
}

MyJNI::~MyJNI()
{
	
}

MyJNI *MyJNI::sharedJNI()
{
	if (!instance)
	{
		instance = new MyJNI();
		instance->autorelease();
	}
	return instance;
}


void MyJNI::showInterstitialAd()
{
	JniMethodInfo methodInfo;
	//bool b = JniHelper::getMethodInfo(methodInfo, "com/zzti/ly/Square", "popShareMenu", "()V");
		
	bool b = JniHelper::getStaticMethodInfo(methodInfo, "com/zzti/ly/Square", "showInterstitialAd", "()V");
	if (b)
	{
		methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
		//jobject obj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
		//methodInfo.env->CallVoidMethod(obj, methodInfo.methodID);

	}
}

void MyJNI::cancelInterstitialAd()
{
	JniMethodInfo methodInfo;
		
	bool b = JniHelper::getStaticMethodInfo(methodInfo, "com/zzti/ly/Square", "cancelInterstitialAd", "()V");
	
	if (b)
	{
		methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	}
}

void MyJNI::showAppWall()
{
	JniMethodInfo methodInfo;
		
	bool b = JniHelper::getStaticMethodInfo(methodInfo, "com/zzti/ly/Square", "showAppWall", "()V");
	if (b)
	{
		methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	}
}

#endif
