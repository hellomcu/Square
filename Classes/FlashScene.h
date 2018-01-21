#ifndef __FLASHSCENE_H__
#define __FLASHSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class FlashScene : public CCLayer
{
public:
	bool init();
	CREATE_FUNC(FlashScene);
	static CCScene * scene();

	void startLoadingScene(float dt);
	
};


#endif