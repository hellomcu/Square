#ifndef __MOREAPPSMENUSQUARE_H__
#define __MOREAPPSMENUSQUARE_H__

#include "cocos2d.h"
#include "MenuSquare.h"

USING_NS_CC;

class MoreAppsMenuSquare : public MenuSquare
{

public:
	static MoreAppsMenuSquare * create(const ccColor4B& color, GLfloat width, GLfloat height);
	void onEnter();
	void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};


#endif
