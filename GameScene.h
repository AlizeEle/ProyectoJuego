#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Player.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void createShootProjectile(cocos2d::Touch* touch);
	void createZombie();
	void update(float delta) override;
	CREATE_FUNC(GameScene);

private:
	Player* player;
	std::vector<cocos2d::Sprite*> _projectiles;
	std::vector<cocos2d::Sprite*> _zombies;

	int zombiesKilled = 0;
};
