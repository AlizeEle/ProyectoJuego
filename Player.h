#pragma once

#include "cocos2d.h"
#include "Bullet.h"

class Player : public cocos2d::Sprite {
public:
    static Player* createPlayer();  // Crear la instancia del jugador
    virtual bool init();  // Inicializar el jugador

    // Método para disparar
    void shoot();

    // Vectores para controlar las balas
    std::vector<Bullet*> bullets;  // Lista de balas disparadas

    // Métodos para la vida
    void reduceHealth(float damage);
    float getHealth() const { return health; }
    bool isDead() const { return health <= 0; }

    // Método para actualizar la barra de vida
    void updateHealthBar();

    // Getter para la barra de vida
    cocos2d::ProgressTimer* getHealthBar() { return healthBar; }

    // Métodos para el movimiento del jugador
    void moveTo(const cocos2d::Vec2& position);  // Mover a una posición específica
    void moveBy(const cocos2d::Vec2& delta);  // Mover por un desplazamiento

private:
    // Método para crear la bala
    void createBullet();

    // Barra de vida
    cocos2d::ProgressTimer* healthBar;  // Barra de vida del jugador
    float health = 100.0f;  // Vida inicial
};
