#include "Square.h"
#include "Constants.h"

Square * Square::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
	Square * pLayer = new Square();
    if( pLayer && pLayer->initWithColor(color, width, height))
	{
		pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void Square::createBody(b2World *world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(this->getPositionX() / RATIO, this->getPositionY() / RATIO);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape  shape;
	CCSize size = this->getContentSize();
	shape.SetAsBox(size.width / RATIO / 2, size.height / RATIO / 2);
	b2FixtureDef fixture;
	fixture.filter.groupIndex = -1;
	fixture.shape = &shape;
	fixture.restitution = 1.0f;
	fixture.friction = 0.0f;
	body->CreateFixture(&fixture);
	body->SetUserData(this);
}

b2Body *Square::getBody()
{
	return body;
}