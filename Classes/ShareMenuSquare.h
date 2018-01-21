#ifndef __SHAREMENUSQUARE_H__
#define __SHAREMENUSQUARE_H__

#include "cocos2d.h"
#include "MenuSquare.h"

USING_NS_CC;

class ShareMenuSquare : public MenuSquare
{

public:
	static ShareMenuSquare * create(const ccColor4B& color, GLfloat width, GLfloat height);
	void onEnter();
	void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};


#endif
