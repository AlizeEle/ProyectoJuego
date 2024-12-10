#include "StoreLayer.h"
#include "LoadingLayer.h"
USING_NS_CC;

cocos2d::Scene* StoreLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = StoreLayer::create();
    scene->addChild(layer);
    return scene;
}

bool StoreLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    // Configura la interfaz de usuario
    this->createUI();

    return true;
}

void StoreLayer::createUI()
{
    // Tamaño de la ventana visible
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Fondo de la tienda
    auto background = DrawNode::create();
    background->drawSolidRect(Vec2(0, 0), visibleSize, Color4F(0.8f, 0.9f, 1.0f, 1.0f));
    background->setPosition(origin);
    this->addChild(background);

    // Etiqueta de título
    auto title = Label::createWithTTF("Store", "fonts/Marker Felt.ttf", 48);
    title->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - title->getContentSize().height));
    title->setColor(Color3B::BLACK);
    this->addChild(title);

    // Botón de volver
    auto backButton = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 36);
    backButton->setColor(Color3B::WHITE);
    backButton->setPosition(Vec2(origin.x + visibleSize.width - backButton->getContentSize().width,
        origin.y + backButton->getContentSize().height));
    this->addChild(backButton);

    // Configurar evento táctil para el botón de volver
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [this, backButton](Touch* touch, Event* event) -> bool {
        Rect backRect(backButton->getPositionX() - backButton->getContentSize().width / 2,
            backButton->getPositionY() - backButton->getContentSize().height / 2,
            backButton->getContentSize().width, backButton->getContentSize().height);

        if (backRect.containsPoint(touch->getLocation())) {
            // Volver a la escena anterior
            auto loadingScene = LoadingLayer::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, loadingScene));
            return true;
        }
        return false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

