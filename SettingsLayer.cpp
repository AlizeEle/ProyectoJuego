#include "SettingsLayer.h"
#include "LoadingLayer.h" // Para volver a la escena de carga

USING_NS_CC;

Scene* SettingsLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingsLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SettingsLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    // Crear la interfaz de usuario
    this->createUI();

    return true;
}

void SettingsLayer::createUI()
{
    // Tamaño de la ventana visible y origen
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Fondo de la capa de configuración
    auto background = DrawNode::create();
    background->drawSolidRect(Vec2(0, 0), visibleSize, Color4F(0.9f, 0.9f, 0.9f, 1.0f)); // Fondo gris claro
    background->setPosition(origin);
    this->addChild(background);

    // Título de la configuración
    auto title = Label::createWithTTF("Settings", "fonts/Marker Felt.ttf", 48);
    if (!title) {
        CCLOG("Error al cargar la fuente");
    }
    title->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - title->getContentSize().height));
    title->setColor(Color3B::BLACK);
    this->addChild(title);

    // Botón para regresar
    this->createBackButton();
}

void SettingsLayer::createBackButton()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Crear etiqueta para el botón "Volver"
    auto backButton = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 36);
    backButton->setColor(Color3B::WHITE);
    backButton->setPosition(Vec2(origin.x + backButton->getContentSize().width,
        origin.y + visibleSize.height - backButton->getContentSize().height));
    this->addChild(backButton);

    // Configurar el evento táctil para el botón
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [this, backButton](Touch* touch, Event* event) -> bool {
        Rect backRect(backButton->getPositionX() - backButton->getContentSize().width / 2,
            backButton->getPositionY() - backButton->getContentSize().height / 2,
            backButton->getContentSize().width, backButton->getContentSize().height);

        if (backRect.containsPoint(touch->getLocation())) {
            // Volver a la escena de carga
            auto loadingScene = LoadingLayer::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, loadingScene));
            return true;
        }
        return false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
