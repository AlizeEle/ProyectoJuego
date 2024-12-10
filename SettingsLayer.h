#pragma once
#include "cocos2d.h"

class SettingsLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingsLayer);

private:
	void createUI();
	void createBackButton();
};