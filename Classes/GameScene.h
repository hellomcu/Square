#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MySquare.h"
#include "Square.h"
#include "AudioMenuSquare.h"

USING_NS_CC;

class GameScene : public CCLayer , public b2ContactListener
{
public:
	static CCScene *scene();
	bool init();
	CREATE_FUNC(GameScene);

	void createWorld();
	void initPoint();
	void createWall();
	void createOtherSquare();
	void createMySquare();
	void createTimeLabel();
	void createMenu();

	void startGame();

	virtual void update(float dt);
	virtual void keyBackClicked();

	void gameOver();
	inline void updateTime();
	inline void changeSpeed(float dt);

	void onEnterTransitionDidFinish();

	void BeginContact(b2Contact *contact);

	bool gameIsStart;
	MySquare *mySquare;

	

private:
	
	b2World *world;
	
	Square *square1, *square2, *square3, *square4;
	//�ĸ������ǽ��
	CCLayerColor *topWall, *bottomWall, *leftWall, *rightWall;
	//ǽ����ĸ���
	CCPoint left_top, right_top, right_bottom, left_bottom;

	CCLabelAtlas *timeLabel;

	float speed;
	float init_time_ms;

	bool audioIsOpen;
};


#endif 