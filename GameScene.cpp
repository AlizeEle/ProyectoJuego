#include "GameScene.h"
#include "LoadingLayer.h"
#include "MainScene.h"
#include "Zombie.h"
#include "Player.h"
#include "Bullet.h"
#include "cocos2d.h"
#include "GameOverScene.h"
#include "WinScene.h"
#include "LevelTwoScene.h"

USING_NS_CC;

/*Scene* GameScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto background = Sprite::create("Background1.png");
    background->setPosition(Vec2(640, 360));
    this->addChild(background);

    // Crear zombies peri�dicamente
    this->schedule([this](float dt) {
        createZombie();
        }, 2.0f, "spawn_zombies");

    // Configurar escucha de toques
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        createShootProjectile(touch);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    scheduleUpdate(); // Programar actualizaciones
    return true;
}

void GameScene::createShootProjectile(Touch* touch) {
    /*auto position = Vec2(640, 360); // Posici�n inicial del proyectil
    auto target = touch->getLocation();
    auto bullet = Bullet::createBullet(position, target);
    if (bullet) {
        this->addChild(bullet);
        bullet->moveToTarget(1.0f);
        _projectiles.push_back(bullet);
    }*/
    /*auto projectile = Sprite::create("bullet.png");
    if (!projectile) {
        CCLOG("Error: No se pudo cargar la imagen de la bala.");
        return;
    }

    // Si la imagen se carga correctamente, se puede continuar
    projectile->setPosition(Vec2(640, 360));
    this->addChild(projectile);

    Vec2 target = touch->getLocation();
    Vec2 direction = target - projectile->getPosition();
    direction.normalize();

    auto moveAction = MoveTo::create(1.0f, target);
    projectile->runAction(moveAction);

    // Agregar a la lista de proyectiles
    _projectiles.push_back(projectile);
}

void GameScene::createZombie() {
    auto zombie = Zombie::createZombie();
    if (zombie) {
        this->addChild(zombie);
        zombie->moveAcrossSceen(5.0f);
        _zombies.push_back(zombie);
    }
}

void GameScene::update(float delta) {
    for (auto projectile : _projectiles) {
        // Verifica que el proyectil no sea nulo
        if (projectile == nullptr) {
            CCLOG("Error: Proyectil nulo en la lista.");
            continue;  // Si el proyectil es nulo, salta a la siguiente iteraci�n
        }

        Rect projectileRect = projectile->getBoundingBox();

        for (auto zombie : _zombies) {
            // Verifica que el zombie no sea nulo
            if (zombie == nullptr) {
                CCLOG("Error: Zombie nulo en la lista.");
                continue;  // Si el zombie es nulo, salta a la siguiente iteraci�n
            }

            Rect zombieRect = zombie->getBoundingBox();

            // Verificamos si los rect�ngulos de colisi�n se superponen
            if (projectileRect.intersectsRect(zombieRect)) {
                // Si hay colisi�n, eliminamos tanto el proyectil como el zombie
                projectile->removeFromParent();
                zombie->removeFromParent();

                // Eliminamos los proyectiles y zombies del vector
                _projectiles.erase(std::remove(_projectiles.begin(), _projectiles.end(), projectile), _projectiles.end());
                _zombies.erase(std::remove(_zombies.begin(), _zombies.end(), zombie), _zombies.end());

                // Opcional: Crear m�s zombies despu�s de eliminar uno
                createZombie();

                break; // Salimos del bucle porque ya hemos procesado esta colisi�n
            }
        }
    }
}
*/

Scene* GameScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // Crear fondo
    auto background = Sprite::create("Background1.png");
    background->setPosition(Vec2(640, 360));
    this->addChild(background);

    // Crear al jugador en la parte inferior central
    player = Player::createPlayer();  // Crear el jugador
    if (player) {
        this->addChild(player);  // A�adirlo a la escena
    }

    // Inicializar el listener de teclas para mover al jugador
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (player) {
            if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
                player->moveBy(Vec2(-10, 0));  // Mover a la izquierda
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
                player->moveBy(Vec2(10, 0));  // Mover a la derecha
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
                player->moveBy(Vec2(0, 10));  // Mover hacia arriba
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
                player->moveBy(Vec2(0, -10));  // Mover hacia abajo
            }
        }
        };

    listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
        // Opcional: Agregar l�gica para cuando se suelta la tecla
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    // Aseg�rate de que la barra de vida se agregue a la escena
    auto healthBar = player->getHealthBar();  // Aseg�rate de tener un getter para la barra de vida si es necesario
    if (healthBar) {
        this->addChild(healthBar);  // A�adir la barra de vida al GameScene
    }

    // Crear zombies peri�dicamente
    this->schedule([this](float dt) {
        createZombie();
        }, RandomHelper::random_real(1.0f, 2.0f), "spawn_zombies");

    // Configurar escucha de toques para disparar
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        createShootProjectile(touch);  // Crear proyectil cuando el jugador toque la pantalla
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    scheduleUpdate(); // Programar actualizaciones de la escena
    return true;
}

void GameScene::createShootProjectile(Touch* touch) {
    // El jugador dispara un proyectil
    auto projectile = Bullet::createBullet(player->getPosition(), touch->getLocation());
    if (projectile) {
        this->addChild(projectile);
        projectile->moveToTarget(1.0f);  // Mover la bala hacia el objetivo en 1 segundo
        _projectiles.push_back(projectile);
    }
}

void GameScene::createZombie() {
    // Crear un zombie y agregarlo a la escena
    auto zombie = Zombie::createZombie();
    if (zombie) {
        this->addChild(zombie);
        zombie->moveAcrossSceen(5.0f);  // Mover el zombie a trav�s de la pantalla
        _zombies.push_back(zombie);
    }
}

void GameScene::update(float delta) {
    // Verificar colisiones entre proyectiles y zombies
    for (auto projectile : _projectiles) {
        if (projectile == nullptr) {
            CCLOG("Error: Proyectil nulo en la lista.");
            continue;
        }

        Rect projectileRect = projectile->getBoundingBox();

        for (auto zombie : _zombies) {
            if (zombie == nullptr) {
                CCLOG("Error: Zombie nulo en la lista.");
                continue;
            }

            // Verificar si zombie es un Sprite v�lido
            auto spriteZombie = dynamic_cast<cocos2d::Sprite*>(zombie);
            if (spriteZombie == nullptr) {
                CCLOG("Error: Zombie no es un Sprite v�lido.");
                continue;
            }

            Rect zombieRect = spriteZombie->getBoundingBox();

            // Verificar colisi�n entre proyectil y zombie
            if (projectileRect.intersectsRect(zombieRect)) {
                // Eliminar el proyectil y el zombie
                projectile->removeFromParent();
                spriteZombie->removeFromParent();

                // Remover de las listas
                _projectiles.erase(std::remove(_projectiles.begin(), _projectiles.end(), projectile), _projectiles.end());
                _zombies.erase(std::remove(_zombies.begin(), _zombies.end(), zombie), _zombies.end());

                // Incrementar el contador de zombies eliminados
                zombiesKilled++;
                CCLOG("Zombies eliminados: %d", zombiesKilled);

                // Verificar si se alcanza la condici�n de victoria
                if (zombiesKilled >= 10) {
                    Director::getInstance()->replaceScene(LevelTwoScene::createScene());
                    return;
                }
                break;  // Salir del bucle de zombies porque este proyectil ya no es v�lido
            }
        }
    }

    // Verificar colisiones entre el jugador y los zombies
    for (auto zombie : _zombies) {
        if (zombie == nullptr) {
            CCLOG("Error: Zombie nulo en la lista.");
            continue;
        }

        auto spriteZombie = dynamic_cast<cocos2d::Sprite*>(zombie);
        if (spriteZombie == nullptr) {
            CCLOG("Error: Zombie no es un Sprite v�lido.");
            continue;
        }

        Rect zombieRect = spriteZombie->getBoundingBox();
        Rect playerRect = player->getBoundingBox();

        // Verificar colisi�n entre el jugador y el zombie
        if (zombieRect.intersectsRect(playerRect)) {
            // Reducir la salud del jugador
            player->reduceHealth(10.0f);

            // Eliminar el zombie
            spriteZombie->removeFromParent();
            _zombies.erase(std::remove(_zombies.begin(), _zombies.end(), zombie), _zombies.end());

            // Verificar si el jugador ha muerto
            if (player->isDead()) {
                CCLOG("�El jugador ha muerto!");
                Director::getInstance()->replaceScene(GameOverScene::createScene());
                return; // Salir del m�todo
            }

            break; // Salir del bucle de zombies
        }
    }
}
