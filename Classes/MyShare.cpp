#include "MyShare.h"
#include <string>

MyShare *_instance = NULL;

MyShare::MyShare()
{
	
}

MyShare::~MyShare()
{
	
}

MyShare *MyShare::getMyShare()
{
	if (!_instance)
	{
		_instance = new MyShare();
		_instance->autorelease();
	}
	return _instance;
}

void MyShare::share(const char* content)
{

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	
	//截图
	saveScreenShot();
	
	
	// 获取一个CCUMSocialSDK实例
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("53daeb76fd98c555780154ed");
   
    // **********************   设置平台信息  ***************************
    sdk->setQQAppIdAndAppKey("1101767715", "4iZAm25HNEeaBE01");
    sdk->setWeiXinAppInfo("wx1b2d92b052a78858","d43195f4dcc4e9de7408776dd9f3b084");
	//sdk->setRenrenAppInfo("270531", "c2491a2b155e4bdf8277f1cce44b261c",
	//		"6791fcf41ab7413c9a079b0529cafa10");
    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
    // sdk->setLaiwangAppInfo("设置来往和来往动态的app id", 
    //              "设置来往和来往动态的app key", "我的应用名");
    // sdk->setFacebookAppId("你的facebook appid");
    //     // 打开或者关闭log
    // sdk->setLogEnable(true) ;


    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl("http://a.app.qq.com/o/simple.jsp?pkgname=com.zzti.ly.square");
    // 设置友盟分享面板上显示的平台
    vector<int>* platforms = new vector<int>();
	platforms->push_back(SINA);
	platforms->push_back(WEIXIN_CIRCLE);
	platforms->push_back(WEIXIN);
	platforms->push_back(QZONE);
	//platforms->push_back(TENCENT_WEIBO);
	//platforms->push_back(QQ);
	//platforms->push_back(DOUBAN);
    //platforms->push_back(RENREN) ;
   
   
    // 设置平台, 在调用分享、授权相关的函数前必须设置SDK支持的平台
    sdk->setPlatforms(platforms) ;

    // 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容，
    // 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.

    sdk->openShare(content, "/data/data/com.zzti.ly.square/files/screenshot.png", share_selector(MyShare::shareCallback));


	#endif

}


void MyShare::shareCallback(int platform, int stCode, string& errorMsg)
{
	
	/*
	if ( stCode == 100 ) 
    {
        CCLog("#### HelloWorld 开始分享");
    }
    else if ( stCode == 200 ) 
    {
        CCLog("#### HelloWorld 分享成功");
    }
    else 
    {
        CCLog("#### HelloWorld 分享出错");
    }

    CCLog("platform num is : %d.", platform);
	*/
}


void MyShare::saveScreenShot()
{

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	 //定义一个屏幕大小的渲染纹理
	CCRenderTexture* pScreen = CCRenderTexture::create(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888);
	 //获得当前的场景指针
	CCScene* pCurScene = CCDirector::sharedDirector()->getRunningScene();
	 //渲染纹理开始捕捉
	pScreen->begin();
	 //当前场景参与绘制
	pCurScene->visit();
	 //结束捕捉
	pScreen->end();
	 //保存为png
	pScreen->saveToFile("screenshot.png", kCCImageFormatPNG);
	CC_SAFE_DELETE(pScreen);

}


