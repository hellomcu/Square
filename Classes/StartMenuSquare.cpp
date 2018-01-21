#include "StartMenuSquare.h"
#include "GameScene.h"

StartMenuSquare * StartMenuSquare::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
	StartMenuSquare * pLayer = new StartMenuSquare();
    if( pLayer && pLayer->initWithColor(color, width, height))
    {
		pLayer->autorelease();
		CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
		const char *s = str->valueForKey("start")->m_sString.c_str();
		CCLabelTTF *label = CCLabelTTF::create(s, "", 40);
		CCSize size = pLayer->getContentSize();
		label->setPosition(ccp(size.width / 2, size.height / 2));
		pLayer->addChild(label);
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void StartMenuSquare::onEnter()
{
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 128, true);
	CCLayerColor::onEnter();
}


bool StartMenuSquare::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (this->boundingBox().containsPoint(pTouch->getLocation()))
	{
		MenuSquare::ccTouchBegan(pTouch, pEvent);
		CCTransitionFade *trans = CCTransitionFade::create(0.5, GameScene::scene());
		CCDirector::sharedDirector()->replaceScene(trans);
		return true;
	}

	return false;
}

void StartMenuSquare::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void StartMenuSquare::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	MenuSquare::ccTouchEnded(pTouch, pEvent);
}

void StartMenuSquare::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


