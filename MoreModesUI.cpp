#include "MoreModesUI.h"
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

cocos2d::Scene* MoreModesUI::createScene()
{
	auto scene = Scene::create();
	auto layer = MoreModesUI::create();
	scene->addChild(layer);

	return scene;
}

bool MoreModesUI::init()
{
	if (!Layer::init()) {
		return false;
	}
	this->addChild(LayerColor::create(Color4B(0 * 40, 0x43, 0x52, 255)));

	createButton();

	return true;
}

void MoreModesUI::createButton()
{
	button = Sprite::create("Background1.png");
	button->setScale(0.16);
	float posX = 50.0f;
	float posY = 600.0f;

	button->setPosition(Vec2(posX, posY));

	this->addChild(button);

	float offsetX = 477.0;
	float offsetY = -28.0;

	button->setPosition(button->getPosition() + Vec2(offsetX, offsetY));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [this](Touch* touch, Event* event)->bool {
		Vec2 touchLocation = touch->getLocation();
		Rect buttonboundingbox = button->getBoundingBox();

		if (buttonboundingbox.containsPoint(touchLocation)) {
			return true;
		}
		return false;
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, button);
}