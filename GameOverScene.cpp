#include "GameOverScene.h"
#include "MainScene.h"
#include "cocos2d.h"

USING_NS_CC;

GameOverScene* GameOverScene::createScene() {
    auto scene = GameOverScene::create();
    return scene;
}

bool GameOverScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // Crear un mensaje de Game Over
    auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 48);
    label->setPosition(Vec2(640, 360));  // Posición en el centro
    this->addChild(label);

    // Volver al menú principal después de 3 segundos
    this->scheduleOnce([](float) {
        Director::getInstance()->replaceScene(MainScene::createScene());
        }, 3.0f, "go_to_main_scene");

    return true;
}