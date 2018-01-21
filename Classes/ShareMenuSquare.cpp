#include "ShareMenuSquare.h"
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MyJNI.h"
#include "MyShare.h"
#endif

ShareMenuSquare * ShareMenuSquare::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
	ShareMenuSquare * pLayer = new ShareMenuSquare();
    if( pLayer && pLayer->initWithColor(color, width, height))
    {
		pLayer->autorelease();
		CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
		const char *s = str->valueForKey("share")->m_sString.c_str();
		CCLabelTTF *label = CCLabelTTF::create(s, "", 40);
		CCSize size = pLayer->getContentSize();
		label->setPosition(ccp(size.width / 2, size.height / 2));
		pLayer->addChild(label);
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void ShareMenuSquare::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 128, true);
}


bool ShareMenuSquare::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	if (this->boundingBox().containsPoint(pTouch->getLocation()))
	{
		MenuSquare::ccTouchBegan(pTouch, pEvent);
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		const char * score = CCString::createWithFormat("%.3f", CCUserDefault::sharedUserDefault()->getFloatForKey("best_time", 0.000f))->getCString();
		char prefix[150] = "我正在玩的一款游戏, 最高分: ";
		char *url = " 去看看,链接: http://a.app.qq.com/o/simple.jsp?pkgname=com.zzti.ly.square";

		strcat(prefix, score);
		strcat(prefix, url);

		MyShare::getMyShare()->share(prefix);
		
		#endif
		return true;
	}

	return false;
}

void ShareMenuSquare::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void ShareMenuSquare::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	MenuSquare::ccTouchEnded(pTouch, pEvent);
}

void ShareMenuSquare::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

