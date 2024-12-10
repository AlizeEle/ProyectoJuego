#pragma once
#include "cocos2d.h"

class Zombie : public cocos2d::Sprite {
public:
    static Zombie* createZombie();
    void moveAcrossSceen(float duration);
    CREATE_FUNC(Zombie);
private:
    Zombie() = default;
};
