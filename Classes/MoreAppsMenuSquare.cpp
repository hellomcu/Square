#include "MoreAppsMenuSquare.h"
#include "GameScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MyJNI.h"
#endif

MoreAppsMenuSquare * MoreAppsMenuSquare::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
	MoreAppsMenuSquare * pLayer = new MoreAppsMenuSquare();
    if( pLayer && pLayer->initWithColor(color, width, height))
    {
		pLayer->autorelease();
		CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
		const char *s = str->valueForKey("more_apps")->m_sString.c_str();
		CCLabelTTF *label = CCLabelTTF::create(s, "", 40);
		CCSize size = pLayer->getContentSize();
		label->setPosition(ccp(size.width / 2, size.height / 2));
		pLayer->addChild(label);
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void MoreAppsMenuSquare::onEnter()
{
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 128, true);
	CCLayerColor::onEnter();
}


bool MoreAppsMenuSquare::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (this->boundingBox().containsPoint(pTouch->getLocation()))
	{
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		
		MenuSquare::ccTouchBegan(pTouch, pEvent);
	
		MyJNI::sharedJNI()->showAppWall();

		#endif

		return true;
	}

	return false;
}

void MoreAppsMenuSquare::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void MoreAppsMenuSquare::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	MenuSquare::ccTouchEnded(pTouch, pEvent);
}

void MoreAppsMenuSquare::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


