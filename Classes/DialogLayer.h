#ifndef __DIALOGLAYER_H__
#define __DIALOGLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class DialogLayer : public CCLayerColor
{

public:
	static DialogLayer * create(const ccColor4B& color, GLfloat width, GLfloat height, char *title);
	void setContent(char *content);
};


#endif
