#include "LoadingLayer.h"
#include "StoreLayer.h"
#include "GameScene.h"
#include "SettingsLayer.h"
#include "MoreModesUI.h"
using namespace cocos2d;
USING_NS_CC;

cocos2d::Scene* LoadingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	//poner el fondo de inicio
	auto background = Sprite::create("Background1.png");
	if (!background) {
		CCLOG("Error: No se pudo cargar la imagen");
		return false;
	}
	background->setPosition(640, 360);
	background->setContentSize(Size(1280, 720));
	this->addChild(background); 

	auto messageLabel = Label::createWithTTF("Nightmare Walker", "fonts/Marker felt.ttf", 83);
	messageLabel->setAnchorPoint(Vec2(0.5, 0));
	float progressBarY = 360;
	float progressBarHeight = 36;
	float offsetAboveProgressBar = 165;
	messageLabel->setPosition(Vec2(640, progressBarY + progressBarHeight / 2 + offsetAboveProgressBar));
	messageLabel->setColor(Color3B::WHITE);

	//Call the function to create the play button
	createPlayButton();
	createSettingButton();
	createStoreButton();
	createYouTubeButton();
	return true;
}

void LoadingLayer::createPlayButton()
{
	//Creaate a play button usando Sreaw	Node
	auto playButton = DrawNode::create();  // Crea el nodo DrawNode
	if (!playButton) {
		CCLOG("Error: No se pudo crear el botón de Play");
		return;  // Si no se crea correctamente, no seguir con la lógica
	}
	this->addChild(playButton);

	//Set the button size and position
	float buttonWidth = 200;
	float buttonHeight = 80;
	playButton->setContentSize(Size(buttonWidth, buttonHeight));

	float offsetX = 0;
	float offsetY = 50;
	Vec2 buttonPosition = Vec2(640 + offsetX, 360 + offsetY);

	//Draw the button with a yellow stroke and brown fill
	Color4F yellow(1.0f, 1.0f, 0.0f, 1.0f);
	Color4F brown(0.6f, 0.4f, 0.2f, 1.0f);

	playButton->drawSolidRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), brown);
	playButton->drawRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), yellow);
	//Poner la ubicación del boton
	playButton->setPosition(buttonPosition);
	//Crear Play label
	auto playLabel = Label::createWithTTF("PLAY", "fonts/Marker felt.ttf", 36);
	playLabel->setPosition(buttonPosition);
	playLabel->setColor(Color3B::WHITE);
	this->addChild(playLabel);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [this, playButton](Touch* touch, Event* event)->bool {
		Rect buttonRect(playButton->getPositionX() - playButton->getContentSize().width / 2,
			playButton->getPositionY() - playButton->getContentSize().height / 2,
			playButton->getContentSize().width, playButton->getContentSize().height);

		if (buttonRect.containsPoint(touch->getLocation())) {
			//Abrir la siguiente escena
			auto gameScene = GameScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
			return true;

		}
		return false;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void LoadingLayer::createYouTubeButton()
{
	auto button = cocos2d::Sprite::create("HelloWorld.png");
	this->addChild(button);
	
	button->setPosition(Vec2(40, 50));
	button->setScale(0.08f);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [this, button](Touch* touch, Event* event)->bool {

		Rect buttonRect(button->getPositionX() - button->getContentSize().width / 2,
			button->getPositionY() - button->getContentSize().height / 2,
			button->getContentSize().width, button->getContentSize().height);

		if (buttonRect.containsPoint(touch->getLocation())) {
			Application::getInstance()->openURL("https://www.youtube.com");
			return true;
		}
		return false;
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void LoadingLayer::createSettingButton()
{
	//play button usando Draw node
	auto settingButton = DrawNode::create();
	this->addChild(settingButton);

	float buttonWidth = 70;
	float buttonHeight = 25;

	float offsetY = -274;
	Vec2 buttonPosition = Vec2(640, 360 + offsetY);

	Color4F yellow(1.0f, 1.0f, 0.0f, 1.0f);
	Color4F brown(0.6f, 0.4f, 0.2f, 1.0f);

	settingButton->drawSolidRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), brown);
	settingButton->drawRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), yellow);

	settingButton->setPosition(buttonPosition);

	float scaleFactor = 3480.0f / 1280.0f;
	settingButton->setScale(scaleFactor);

	//Create th e PLAY text with manually betwwen letters
	std::string SettingsText = "S E T T I N G S";
	auto settingsLabel = Label::createWithTTF(SettingsText, "fonts/Marker Felt.ttf", 36);
	settingsLabel->setPosition(buttonPosition);
	settingsLabel->setColor(Color3B::WHITE);
	this->addChild(settingsLabel);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [this, settingButton](Touch* touch, Event* event)->bool {
		Rect buttonRect(settingButton->getPositionX() - settingButton->getContentSize().width / 2,
			settingButton->getPositionY() - settingButton->getContentSize().height / 2,
			settingButton->getContentSize().width, settingButton->getContentSize().height);

		if (buttonRect.containsPoint(touch->getLocation())) {
			auto SettingScene = SettingsLayer::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, SettingScene));
		}
		return false;
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		
}

void LoadingLayer::createStoreButton()
{
	auto storeButton = DrawNode::create();
	this->addChild(storeButton);

	float buttonWidth = 237;
	float buttonHeight = 80;
	storeButton->setContentSize(Size(buttonWidth, buttonHeight));
	float offsetX = 0;
	float offsetY = -196;

	Vec2 buttonPos = Vec2(640 + offsetX, 360 + offsetY);

	Color4F yellow(1.0f, 1.0f, 0.0f, 1.0f);
	Color4F brown(0.6f, 0.4f, 0.2f, 1.0f);

	storeButton->drawSolidRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), brown);
	storeButton->drawRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), yellow);

	storeButton->setPosition(buttonPos);

	auto storeBtn = Label::createWithTTF("Store", "fonts/Marker felt.ttf", 36);
	storeBtn->setPosition(buttonPos);
	storeBtn->setColor(Color3B::WHITE);
	this->addChild(storeBtn);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [this, storeBtn](Touch* touch, Event* event)->bool {
		Rect buttonRect(storeBtn->getPositionX() - storeBtn->getContentSize().width / 2,
			storeBtn->getPositionY() - storeBtn->getContentSize().height / 2,
			storeBtn->getContentSize().width, storeBtn->getContentSize().height);

		if (buttonRect.containsPoint(touch->getLocation())) {
			//Abrir la siguiente escena
			auto StoreScene= StoreLayer::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, StoreScene));
			return true;

		}
		return false;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void LoadingLayer::createMoreGameModes()
{
	auto moreModes = DrawNode::create();
	this->addChild(moreModes);

	float buttonWidth = 237;
	float buttonHeight = 80;
	moreModes->setContentSize(Size(buttonWidth, buttonHeight));

	float offsetX = 0;
	float offsetY = -65;
	Vec2 buttonPosition = Vec2(640 + offsetX, 360 + offsetY);

	Color4F yellow(1.0f, 1.0f, 0.0f, 1.0f);
	Color4F brown(0.6f, 0.4f, 0.2f, 1.0f);

	moreModes->drawSolidRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), brown);
	moreModes->drawRect(Vec2(-buttonWidth / 2, -buttonHeight / 2), Vec2(buttonWidth / 2, buttonHeight / 2), yellow);

	moreModes->setPosition(buttonPosition);

	auto moreGameModes = Label::createWithTTF("More GameModes", "fonts/Marker felt.ttf", 36);
	moreGameModes->setPosition(buttonPosition);
	moreGameModes->setColor(Color3B::WHITE);
	this->addChild(moreGameModes);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	
	touchListener->onTouchBegan = [this, moreModes](Touch* touch, Event* event)->bool {
		Rect buttonRect(moreModes->getPositionX() - moreModes->getContentSize().width / 2,
			moreModes->getPositionY() - moreModes->getContentSize().height / 2,
			moreModes->getContentSize().width, moreModes->getContentSize().height);

		if (buttonRect.containsPoint(touch->getLocation())) {
			//Abrir la siguiente escena
			auto MoreModesUI = MoreModesUI::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MoreModesUI));
			return true;

		}
		return false;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
