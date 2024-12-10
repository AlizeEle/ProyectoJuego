#include "Zombie.h"
USING_NS_CC;

Zombie* Zombie::createZombie()
{
    Zombie* zombie = new (std::nothrow) Zombie();
    if (zombie && zombie->initWithFile("zombie.png")) {
        zombie->autorelease();

        //Cambiar la escala
        zombie->setScale(0.5f);
        return zombie;
    }
    CC_SAFE_DELETE(zombie);
    CCLOG("Error: No se pudo crear el zombie.");
    return nullptr;
}

void Zombie::moveAcrossSceen(float duration)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int startPosition = RandomHelper::random_int(0, 3); // 0: derecha, 1: izquierda, 2: arriba, 3: abajo
    float startX, startY;

    switch (startPosition) {
    case 0: // Desde la derecha
        startX = visibleSize.width + this->getContentSize().width / 2;
        startY = RandomHelper::random_int(0, static_cast<int>(visibleSize.height));
        break;
    case 1: // Desde la izquierda
        startX = -this->getContentSize().width / 2;
        startY = RandomHelper::random_int(0, static_cast<int>(visibleSize.height));
        break;
    case 2: // Desde la parte superior
        startX = RandomHelper::random_int(0, static_cast<int>(visibleSize.width));
        startY = visibleSize.height + this->getContentSize().height / 2;
        break;
    case 3: // Desde la parte inferior
        startX = RandomHelper::random_int(0, static_cast<int>(visibleSize.width));
        startY = -this->getContentSize().height / 2;
        break;
    }

    this->setPosition(Vec2(startX, startY));

    // Mover al zombie a través de la pantalla
    auto moveAction = MoveTo::create(duration, Vec2(visibleSize.width / 2, visibleSize.height / 2));
    auto removeAction = RemoveSelf::create();
    this->runAction(Sequence::create(moveAction, removeAction, nullptr));
}
