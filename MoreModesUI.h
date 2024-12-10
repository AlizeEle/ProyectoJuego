#pragma once
#include "cocos2d.h"
class MoreModesUI : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MoreModesUI);

private:

	cocos2d::Sprite* button;
	void createButton();
};