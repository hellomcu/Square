#ifndef __MENUSQUARE_H__
#define __MENUSQUARE_H__

#include "cocos2d.h"


USING_NS_CC;


class MenuSquare : public CCLayerColor
{

public:
	static MenuSquare * create(const ccColor4B& color, GLfloat width, GLfloat height);
	
	CC_SYNTHESIZE(CCLayer *, _layer, Layer);
	void onEnter();
	void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) = 0;
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) = 0;
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) = 0;
};


#endif
