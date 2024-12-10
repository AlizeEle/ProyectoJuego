#include "Bullet.h"
#include "cocos2d.h"

USING_NS_CC;

Bullet* Bullet::createBullet(const Vec2& position, const Vec2& target) {
    Bullet* bullet = new Bullet();
    if (bullet && bullet->initWithFile("bullet.png")) {  // Asegúrate de tener la imagen de la bala
        bullet->autorelease();
        bullet->setPosition(position);
        bullet->direction = target - position;
        bullet->direction.normalize();
        bullet->setScale(0.10f);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}

void Bullet::moveToTarget(float duration) {
    // Mover la bala hacia el objetivo
    auto moveAction = MoveTo::create(duration, this->getPosition() + direction * 1000);  // Distancia
    this->runAction(moveAction);
}
