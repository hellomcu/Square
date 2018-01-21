#include "MySquare.h"
#include "GameScene.h"
#include "Constants.h"

MySquare * MySquare::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
	MySquare * pLayer = new MySquare();
    if( pLayer && pLayer->initWithColor(color, width, height))
    {
		pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void MySquare::onEnter()
{
	isTouch = false;
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayerColor::onEnter();
}


bool MySquare::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (this->boundingBox().containsPoint(pTouch->getLocation()))
	{
		isTouch = true;
		CCPoint location = pTouch->getLocation();
		//b2Body *body = this->body;
		/*b2MouseJointDef mouseJointDef;
		b2BodyDef bodyDef;
		mouseJointDef.bodyA = body->GetWorld()->CreateBody(&bodyDef);
		mouseJointDef.bodyB = body;
		mouseJointDef.target = b2Vec2(location.x / RATIO, location.y / RATIO);
		mouseJointDef.collideConnected = true;
		mouseJointDef.dampingRatio = 1.0f;
		mouseJointDef.maxForce = 999999999.0f;
		mouseJoint = (b2MouseJoint *)body->GetWorld()->CreateJoint(&mouseJointDef);
		body->SetAwake(true);*/
		if (this->_gameScene->gameIsStart)
		{
			return true;
		}
		_gameScene->startGame();
		return true;
	}
	else
	{
		return false;
	}
}

void MySquare::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (isTouch)
	{
		CCPoint location = pTouch->getLocation();
		b2Vec2 vec = b2Vec2(location.x / RATIO, location.y / RATIO);
		b2Body *body = getBody();
		body->SetTransform(vec, 0);
		//mouseJoint->SetTarget(vec);
	}
}

void MySquare::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	isTouch = false;
	//if (mouseJoint)
	//{
		//body->GetWorld()->DestroyJoint(mouseJoint);
		//mouseJoint = NULL;
	//}
}

void MySquare::createBody(b2World *world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(this->getPositionX() / RATIO, this->getPositionY() / RATIO);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape  shape;
	CCSize size = this->getContentSize();
	shape.SetAsBox(size.width / RATIO / 2, size.height / RATIO / 2);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.friction = 1.0f;
	//fixture.filter.groupIndex = -1;
	body->CreateFixture(&fixture);
	body->SetUserData(this);
}

b2Body *MySquare::getBody()
{
	return body;
}