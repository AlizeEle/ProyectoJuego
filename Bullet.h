#pragma once
#include "cocos2d.h"

class Zombie;  // Declaraci�n anticipada de la clase Zombie

class Bullet : public cocos2d::Sprite {
public:
    static Bullet* createBullet(const cocos2d::Vec2& position, const cocos2d::Vec2& target);
    void moveToTarget(float duration);

    CREATE_FUNC(Bullet);

private:
    cocos2d::Vec2 direction;  // Direcci�n en la que se mueve la bala
    Bullet() = default;
};
