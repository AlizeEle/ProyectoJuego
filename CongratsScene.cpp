#include "CongratsScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* CongratsScene::createScene() {
    auto scene = Scene::create();
    auto layer = CongratsScene::create();
    scene->addChild(layer);
    return scene;
}

bool CongratsScene::init() {
    if (!Scene::init()) {
        return false;
    }


    // Mensaje de felicitaciones
    auto label = Label::createWithTTF("¡Felicidades!\nHas ganado el juego.", "fonts/Marker Felt.ttf", 48);
    label->setPosition(Vec2(640, 360));
    this->addChild(label);

    // Volver al menú principal después de unos segundos
    this->scheduleOnce([](float) {
        Director::getInstance()->replaceScene(MainScene::createScene());
        }, 5.0f, "return_to_main");

    return true;
}
