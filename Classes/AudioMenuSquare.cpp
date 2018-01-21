#include "AudioMenuSquare.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

AudioMenuSquare * AudioMenuSquare::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
	AudioMenuSquare * pLayer = new AudioMenuSquare();
    if( pLayer && pLayer->initWithColor(color, width, height))
    {
		pLayer->autorelease();
		bool audioIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey("audio", true);
		CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
		const char *s1 = str->valueForKey("audio_close")->m_sString.c_str();
		pLayer->label = CCLabelTTF::create(s1, "", 40);
		CCSize size = pLayer->getContentSize();
		pLayer->label->setPosition(ccp(size.width / 2, size.height / 2));
		pLayer->addChild(pLayer->label);
		if (audioIsOpen)
		{
			const char *s2 = str->valueForKey("audio_open")->m_sString.c_str();
			pLayer->label->setString(s2);
		}
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void AudioMenuSquare::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 128, true);
	CCLayerColor::onEnter();
}


bool AudioMenuSquare::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (this->boundingBox().containsPoint(pTouch->getLocation()))
	{
		MenuSquare::ccTouchBegan(pTouch, pEvent);
		bool audioIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey("audio", true);
		audioIsOpen = !audioIsOpen;
		if (audioIsOpen)
		{
			CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
			const char *s2 = str->valueForKey("audio_open")->m_sString.c_str();
			label->setString(s2);
		}
		else
		{
			CCDictionary * str = CCDictionary::createWithContentsOfFile("strings.xml");
			const char *s2 = str->valueForKey("audio_close")->m_sString.c_str();
			label->setString(s2);
		}
		CCUserDefault::sharedUserDefault()->setBoolForKey("audio", audioIsOpen);
		return true;
	}
	return false;
}

void AudioMenuSquare::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void AudioMenuSquare::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	MenuSquare::ccTouchEnded(pTouch, pEvent);
}

void AudioMenuSquare::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
