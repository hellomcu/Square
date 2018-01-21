#include "DialogLayer.h"

DialogLayer * DialogLayer::create(const ccColor4B& color, GLfloat width, GLfloat height, char *title)
{
	DialogLayer * pLayer = new DialogLayer();
    if( pLayer && pLayer->initWithColor(color, width, height))
    {
		pLayer->autorelease();
		CCLabelTTF *label = CCLabelTTF::create(title, "", 20);
		CCSize size = pLayer->getContentSize();
		label->setPosition(ccp(10, size.height - 10));
		pLayer->addChild(label);
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}


void DialogLayer::setContent(char *content)
{
	CCLabelTTF *label = CCLabelTTF::create(content, "", 25);
	CCSize size = this->getContentSize();
	label->setPosition(ccp(10, size.height - 30));
	this->addChild(label);
}
