#include "WinScene.h"
#include "MainScene.h"
#include "cocos2d.h"
#include "LevelTwoScene.h"
USING_NS_CC;

cocos2d::Scene* WinScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WinScene::create();
    scene->addChild(layer);
    return scene;
}

bool WinScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    // Mostrar mensaje de victoria
    auto label = Label::createWithTTF("¡Ganaste! Nivel 2 comienza pronto", "fonts/Marker Felt.ttf", 48);
    label->setPosition(Vec2(640, 360));
    this->addChild(label);

    // Cargar el segundo nivel después de unos segundos
    this->scheduleOnce([](float) {
        Director::getInstance()->replaceScene(LevelTwoScene::createScene());
        }, 3.0f, "go_to_level_two");

    return true;
}