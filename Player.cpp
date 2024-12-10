#include "Player.h"
#include "Bullet.h"
#include "cocos2d.h"

USING_NS_CC;

Player* Player::createPlayer() {
    Player* player = new Player();
    if (player && player->init()) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

bool Player::init() {
    if (!Sprite::initWithFile("player.png")) {  // Asegúrate de tener la imagen del jugador
        return false;
    }

    setPosition(Vec2(640, 50));  // Coloca al jugador en la parte inferior de la pantalla

    // Crear la barra de vida
    auto barSprite = Sprite::create();
    barSprite->setTextureRect(Rect(0, 0, 200, 20));  // Tamaño de la barra de vida
    barSprite->setColor(Color3B::RED);  // Color de la barra de vida
    healthBar = ProgressTimer::create(barSprite);
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5));  // Dirección de la barra
    healthBar->setBarChangeRate(Vec2(1, 0));  // Solo cambia de izquierda a derecha
    healthBar->setPercentage(health);  // Establecer el porcentaje de vida inicial
    healthBar->setPosition(Vec2(640, 90));  // Colocar la barra de vida justo arriba del jugador

    // Asegurarse de que el jugador esté en la escena antes de agregar la barra de vida
    auto parentNode = this->getParent();
    if (parentNode) {
        parentNode->addChild(healthBar);  // Añadir la barra de vida al nodo de la escena
    }
    else {
        CCLOG("Error: El jugador no tiene un nodo padre. La barra de vida no se puede agregar.");
    }

    // Inicializar el movimiento
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            moveBy(Vec2(-10, 0));  // Mover a la izquierda
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            moveBy(Vec2(10, 0));  // Mover a la derecha
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            moveBy(Vec2(0, 10));  // Mover hacia arriba
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            moveBy(Vec2(0, -10));  // Mover hacia abajo
        }
        };
    listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
        // Opcional: Agregar lógica para cuando se suelta la tecla
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Player::shoot() {
    createBullet();  // Llamamos al método createBullet()
}

void Player::createBullet() {
    Bullet* bullet = Bullet::createBullet(this->getPosition(), Vec2(640, 480));  // Dirección de disparo
    this->getParent()->addChild(bullet);  // Añadir la bala a la escena
    bullets.push_back(bullet);  // Guardar la bala en el vector
}

void Player::reduceHealth(float damage) {
    health -= damage;  // Reducir la vida
    if (health < 0) {
        health = 0;  // Asegurarse de que la vida no sea negativa
    }
    updateHealthBar();  // Actualizar la barra de vida
}

void Player::updateHealthBar() {
    if (healthBar) {
        healthBar->setPercentage(health);  // Establecer el nuevo porcentaje de vida en la barra
    }
}

void Player::moveTo(const Vec2& position) {
    setPosition(position);  // Establecer la nueva posición del jugador
}

void Player::moveBy(const Vec2& delta) {
    // Mover al jugador por un desplazamiento y limitar su movimiento dentro de la pantalla
    auto newPosition = getPosition() + delta;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float newX = std::max(0.0f, std::min(newPosition.x, visibleSize.width));
    float newY = std::max(0.0f, std::min(newPosition.y, visibleSize.height));
    setPosition(Vec2(newX, newY));
}
