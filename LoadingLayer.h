#pragma once
#include "cocos2d.h"
class LoadingLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	cocos2d::Label* messageLabel;
	static const cocos2d::Color3B golden3B;

	void createPlayButton();
	void createYouTubeButton();
	void createSettingButton();
	void createStoreButton();
	void createMoreGameModes();


private:
	CREATE_FUNC(LoadingLayer);
};