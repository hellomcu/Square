#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "cocos2d.h"

USING_NS_CC;

#define RATIO 48.0f

#define WINSIZE CCDirector::sharedDirector()->getWinSize()
//墙壁宽度
#define WALL_WIDTH 30
//墙壁尺寸
#define WALL_SIZE 30
//墙壁长度
#define WALL_LENGTH WINSIZE.width
#define WALL_HEIGHT WINSIZE.height
//最大移动距离为墙壁范围对角线长度
#define MAX_DISTANCE ccp(0, 0).getDistance(ccp(WALL_LENGTH, WALL_LENGTH))

//速度的增加倍数
#define SPEED_INCREMENT 1.05f

#endif
