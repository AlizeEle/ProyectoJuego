#pragma once
#include "MainScene.h"
#include "cocos2d.h"


class GameOverScene : public cocos2d::Scene
{
public:
	static GameOverScene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOverScene);
};