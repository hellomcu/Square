#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class Square : public CCLayerColor
{
public:
	static Square * create(const ccColor4B& color, GLfloat width, GLfloat height);
	
	void createBody(b2World *world);

	b2Body *getBody();

private:
	b2Body *body;
};


#endif
