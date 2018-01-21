#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class LoadingScene : public CCLayer
{
public:
	bool init();
	CREATE_FUNC(LoadingScene);
	static CCScene * scene();
	virtual void keyBackClicked();
	void exitGameCallback(CCObject* pSender);
	void cancelCallback(CCObject* pSender);
	void createMenu();
	void onEnterTransitionDidFinish();

};


#endif