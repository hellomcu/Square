#ifndef __MYSQUARE_H__
#define __MYSQUARE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class GameScene;

class MySquare : public CCLayerColor
{
private:
	bool isTouch;
	b2Body *body;
	//b2MouseJoint *mouseJoint;
public:
	static MySquare * create(const ccColor4B& color, GLfloat width, GLfloat height);
	void onEnter();
	CC_SYNTHESIZE(GameScene *, _gameScene, Scene);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void createBody(b2World *world);
	b2Body *getBody();
};


#endif
