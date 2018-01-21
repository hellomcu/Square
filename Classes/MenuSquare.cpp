#include "MenuSquare.h"




bool MenuSquare::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	this->setScale(0.95f);
	return true;
}

void MenuSquare::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	this->setScale(1.0f);
}

void MenuSquare::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 128, true);
	CCLayerColor::onEnter();
}

void MenuSquare::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
