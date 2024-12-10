#include "LevelTwoScene.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "cocos2d.h"
#include "GameOverScene.h"
#include "WinScene.h"

USING_NS_CC;

Scene* LevelTwoScene::createScene() {
    auto scene = Scene::create();
    auto layer = LevelTwoScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelTwoScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // Crear fondo
    auto background = Sprite::create("Background2.png");
    background->setPosition(Vec2(640, 360));
    this->addChild(background);

    // Crear al jugador en la parte inferior central
    player = Player::createPlayer();  // Crear el jugador
    if (player) {
        this->addChild(player);  // Añadirlo a la escena
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
        // Opcional: Agregar lógica para cuando se suelta la tecla
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    // Crear zombies periódicamente
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

void LevelTwoScene::createShootProjectile(Touch* touch) {
    // El jugador dispara un proyectil
    auto projectile = Bullet::createBullet(player->getPosition(), touch->getLocation());
    if (projectile) {
        this->addChild(projectile);
        projectile->moveToTarget(1.0f);  // Mover la bala hacia el objetivo en 1 segundo
        _projectiles.push_back(projectile);
    }
}

void LevelTwoScene::createZombie() {
    // Crear un zombie y agregarlo a la escena
    auto zombie = Zombie::createZombie();
    if (zombie) {
        this->addChild(zombie);
        zombie->moveAcrossSceen(5.0f);  // Mover el zombie a través de la pantalla
        _zombies.push_back(zombie);
    }
}

void LevelTwoScene::update(float delta) {
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

            // Asegúrate de que 'zombie' es un Sprite
            auto spriteZombie = dynamic_cast<cocos2d::Sprite*>(zombie);
            if (spriteZombie == nullptr) {
                CCLOG("Error: Zombie no es un Sprite válido.");
                continue;  // Si no es un Sprite, salta a la siguiente iteración
            }

            Rect zombieRect = spriteZombie->getBoundingBox();

            // Verificar colisión entre proyectil y zombie
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

                // Verificar si se alcanza la condición de victoria
                if (zombiesKilled >= 20) {  // Por ejemplo, si el jugador mata 10 zombies gana
                    Director::getInstance()->replaceScene(MainScene::createScene());
                    return;
                }
                break;  // Salir del bucle porque ya hemos procesado esta colisión
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
            CCLOG("Error: Zombie no es un Sprite válido.");
            continue;
        }

        Rect zombieRect = spriteZombie->getBoundingBox();
        Rect playerRect = player->getBoundingBox();

        // Verificar colisión entre el jugador y el zombie
        if (zombieRect.intersectsRect(playerRect)) {
            // Reducir la salud del jugador
            player->reduceHealth(10.0f);

            // Eliminar el zombie
            spriteZombie->removeFromParent();
            _zombies.erase(std::remove(_zombies.begin(), _zombies.end(), zombie), _zombies.end());

            // Verificar si el jugador ha muerto
            if (player->isDead()) {
                CCLOG("¡El jugador ha muerto!");
                Director::getInstance()->replaceScene(GameOverScene::createScene());
                return; // Salir del método
            }

            break; // Salir del bucle de zombies
        }
    }
}