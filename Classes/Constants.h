#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "cocos2d.h"

USING_NS_CC;

#define RATIO 48.0f

#define WINSIZE CCDirector::sharedDirector()->getWinSize()
//ǽ�ڿ��
#define WALL_WIDTH 30
//ǽ�ڳߴ�
#define WALL_SIZE 30
//ǽ�ڳ���
#define WALL_LENGTH WINSIZE.width
#define WALL_HEIGHT WINSIZE.height
//����ƶ�����Ϊǽ�ڷ�Χ�Խ��߳���
#define MAX_DISTANCE ccp(0, 0).getDistance(ccp(WALL_LENGTH, WALL_LENGTH))

//�ٶȵ����ӱ���
#define SPEED_INCREMENT 1.05f

#endif
