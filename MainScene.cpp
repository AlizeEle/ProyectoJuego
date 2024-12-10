#include "MainScene.h"
#include "LoadingLayer.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d;
USING_NS_CC;

cocos2d::Scene* MainScene::createScene()
{
    auto scene = Scene::create(); // Crea la escena
    auto layer = MainScene::create(); // Crea la capa
    scene->addChild(layer); // Agrega la capa a la escena
    return scene; // Devuelve la escena
}

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    AudioEngine::play2d("Musica.mp3", true);

    // Inicializa la etiqueta con un mensaje aleatorio al inicio
    messageLabel = Label::createWithTTF(getRandomMessage(), "fonts/Marker Felt.ttf", 31);
    messageLabel->setPosition(Vec2(640, 50));
    this->addChild(messageLabel);

    // Agregar el segundo mensaje
    auto messageLabel2 = Label::createWithTTF("cocos2dx", "fonts/Marker Felt.ttf", 27);
    messageLabel2->setPosition(Vec2(10, 10));
    messageLabel2->setAnchorPoint(Vec2(0, 0));
    messageLabel2->setColor(Color3B::WHITE);
    this->addChild(messageLabel2);

    // Agregar el tercer mensaje
    auto messageLabel3 = Label::createWithTTF("Eleonor", "fonts/Marker Felt.ttf", 27);
    messageLabel3->setPosition(Vec2(1, 10));
    messageLabel3->setAnchorPoint(Vec2(1270, 0));
    messageLabel3->setColor(Color3B::WHITE);
    this->addChild(messageLabel3);

    // Mensaje sobre el segundo
    auto messageLabelAbove = Label::createWithTTF("Vergara", "fonts/Marker Felt.ttf", 24);
    messageLabelAbove->setAnchorPoint(Vec2(1, 0));
    float verticalOffset = messageLabel2->getContentSize().height + 5;
    messageLabelAbove->setPosition(Vec2(1270, 10 + verticalOffset));
    messageLabelAbove->setColor(Color3B::BLUE);
    this->addChild(messageLabelAbove);

    // Agregar el cuarto mensaje
    auto messageLabel4 = Label::createWithTTF("Resident Evil", "fonts/Marker Felt.ttf", 83);
    messageLabel4->setAnchorPoint(Vec2(0.5, 0));
    float progressBarY = 360;
    float progressBarHeight = 36;
    float offsetAboveProgressBar = 165;
    messageLabel4->setPosition(Vec2(640, progressBarY + progressBarHeight / 2 + offsetAboveProgressBar));
    messageLabel4->setColor(Color3B::WHITE);
    this->addChild(messageLabel4);

    // Poner la barra de progreso
    auto progressBarBackground = Sprite::create();
    progressBarBackground->setTextureRect(Rect(0, 0, 348, 10));
    progressBarBackground->setColor(Color3B::GRAY);
    progressBarBackground->setPosition(Vec2(640, 360));
    this->addChild(progressBarBackground);

    // Crear la barra de progreso con las dimensiones
    auto barSprite = Sprite::create();
    barSprite->setTextureRect(Rect(0, 0, 348, 10));
    barSprite->setColor(Color3B::BLUE); // El color de la barra de progreso es azul

    progressBar = ProgressTimer::create(barSprite);
    progressBar->setType(ProgressTimer::Type::BAR);
    progressBar->setMidpoint(Vec2(0, 0.5));
    progressBar->setBarChangeRate(Vec2(1, 0));
    progressBar->setPercentage(0); // Inicia desde cero
    progressBar->setPosition(Vec2(640, 360));
    this->addChild(progressBar);

    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::updateProgressBar), 0.1f);
    return true;
}

std::string MainScene::getRandomMessage()
{
    int randomIndex = cocos2d::RandomHelper::random_int(1, 100);

    switch (randomIndex) {
    case 1: return "¡Listos para la aventura!"; break;
    case 2: return "Bienvenidos al apocalipsis Zombie"; break;
    case 3: return "Te han matado"; break;
    default: return "Bien hecho, lo hiciste genial";
    }
}

void MainScene::updateProgressBar(float dt)
{
    float percent = progressBar->getPercentage();
    if (percent < 100) {
        progressBar->setPercentage(percent + 2); // Aumenta la barra
    }
    else {
        // Cuando la barra llegue a 100 va a pasar a la siguiente escena
        this->unschedule(CC_SCHEDULE_SELECTOR(MainScene::updateProgressBar));
        auto loadingScene = LoadingLayer::createScene();
        Director::getInstance()->replaceScene(loadingScene); // Reemplaza la escena actual por la de LoadingLayer
    }
}
