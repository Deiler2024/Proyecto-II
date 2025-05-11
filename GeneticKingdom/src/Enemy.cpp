#include "Enemy.h"
#include <iostream> // Opcional para debug

Enemy::Enemy(float health, float speed, float arrowRes, float magicRes, float artilleryRes)
    : health(health), speed(speed),
      arrowResistance(arrowRes), magicResistance(magicRes), artilleryResistance(artilleryRes),
      position(0.f, 0.f) {}

void Enemy::takeDamage(float amount, const std::string& damageType) {
    if (damageType == "arrow") {
        amount *= (1.0f - arrowResistance);
    } else if (damageType == "magic") {
        amount *= (1.0f - magicResistance);
    } else if (damageType == "artillery") {
        amount *= (1.0f - artilleryResistance);
    }

    health -= amount;

    std::cout << "Daño recibido: " << amount << ", Vida restante: " << health << std::endl;

    if (health <= 0.f) {
        health = 0.f; // No vida negativa
        // Aquí podrías marcar que el enemigo está muerto si quieres
    }
}

float Enemy::getHealth() const {
    return health;
}

sf::Vector2f Enemy::getPosition() const {
    return position;
}
