#ifndef __OVERDIALOG_H__
#define __OVERDIALOG_H__

#include "cocos2d.h"


USING_NS_CC;


class OverDialog : public CCLayerColor
{

public:
	static OverDialog * create(const ccColor4B& color, GLfloat width, GLfloat height, char *title);
	void setContent(const char *content, const ccColor3B& color);
	
	void cancelMenu(CCObject *p);
	

	void setScore(const std::string score);
	const char* getScore();

	void shareScore(CCObject *p);


private:
	std::string _score;
};


#endif
