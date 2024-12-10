#pragma once
#include "MainScene.h"
#include "cocos2d.h"

class WinScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WinScene);
};