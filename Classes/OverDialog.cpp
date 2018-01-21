#include "OverDialog.h"
#include "GameScene.h"
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MyJNI.h"
#include "MyShare.h"
#endif

OverDialog * OverDialog::create(const ccColor4B& color, GLfloat width, GLfloat height, char *title)
{
	OverDialog * pLayer = new OverDialog();
    if( pLayer && pLayer->initWithColor(color, width, height))
    {
		//pLayer->_score = (char *)malloc(10);
		
		pLayer->autorelease();
		pLayer->ignoreAnchorPointForPosition(false);
		CCLabelTTF *label = CCLabelTTF::create(title, "", 30);
		CCSize size = pLayer->getContentSize();
		label->setPosition(ccp(size.width / 2, size.height - 40));
		pLayer->addChild(label);

		CCLayerColor *cancelLayer = CCLayerColor::create(ccc4(43, 113, 255,255), size.width / 2 - 15, height / 3);
		CCLayerColor *cancelLayer2 = CCLayerColor::create(ccc4(43, 113, 255,255), size.width / 2 - 20, height / 3.5f);
		cancelLayer->ignoreAnchorPointForPosition(false);
		cancelLayer2->ignoreAnchorPointForPosition(false);
		cancelLayer->setAnchorPoint(ccp(0.5f, 0.5f));
		cancelLayer2->setAnchorPoint(ccp(0.5f, 0.5f));
		CCSize btnSize = cancelLayer->getContentSize();
		CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
		const char *s1 = str->valueForKey("continue_game")->m_sString.c_str();
		CCLabelTTF *cancelLabel = CCLabelTTF::create(s1, "", 35);
		cancelLabel->setPosition(ccp(btnSize.width / 2, btnSize.height / 2));
		cancelLayer->addChild(cancelLabel);
		//cancelLayer2->addChild(cancelLabel);
		CCMenuItemSprite *cancelMenu = CCMenuItemSprite::create(cancelLayer, cancelLayer, pLayer, menu_selector(OverDialog::cancelMenu));
		cancelMenu->setPosition(ccp(btnSize.width / 2 + 10, btnSize.height / 2 + 10));
		
		CCLayerColor *shareLayer = CCLayerColor::create(ccc4(255, 0, 128, 255), size.width / 2 - 15, height / 3);
		const char *s2 = str->valueForKey("share_score")->m_sString.c_str();
		CCLabelTTF *shareLabel = CCLabelTTF::create(s2, "", 35);
		shareLabel->setPosition(ccp(btnSize.width / 2, btnSize.height / 2));
		shareLayer->addChild(shareLabel);
		CCMenuItemSprite *shareMenu = CCMenuItemSprite::create(shareLayer, shareLayer, pLayer, menu_selector(OverDialog::shareScore));
		shareMenu->setPosition(ccp(btnSize.width * 1.5f + 20, btnSize.height / 2 + 10));
		CCMenu *menu = CCMenu::create(cancelMenu, shareMenu, NULL);
		menu->setPosition(ccp(0, 0));
		pLayer->addChild(menu);

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		MyJNI::sharedJNI()->showInterstitialAd();
		#endif

        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void OverDialog::setContent(const char *content, const ccColor3B& color)
{
	CCLabelTTF *label = CCLabelTTF::create(content, "", 50);
	label->setColor(color);
	CCSize size = this->getContentSize();
	label->setPosition(ccp(size.width / 2, size.height / 2 + 20));
	this->addChild(label);
}


void OverDialog::setScore(const std::string score)
{
	_score = score;
}

const char* OverDialog::getScore()
{
	return _score.c_str();
}


void OverDialog::cancelMenu(CCObject *p)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	MyJNI::sharedJNI()->cancelInterstitialAd();
	#endif
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void OverDialog::shareScore(CCObject *p)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	const char* score = getScore();
	char prefix[150] = "我正在玩的一款游戏, 得分: ";
	char *url = " 去看看,链接: http://a.app.qq.com/o/simple.jsp?pkgname=com.zzti.ly.square";
	strcat(prefix, score);
	strcat(prefix, url);

	MyShare::getMyShare()->share(prefix);
	#endif
}

