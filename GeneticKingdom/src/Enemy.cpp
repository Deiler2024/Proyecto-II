#include "Enemy.h"               // *Incluye la declaración de la clase Enemy*
#include "Harpy.h"
#include <iostream>              // *Incluye funcionalidades para imprimir en consola (debug)*

// 🔧 Constructor: inicializa los atributos del enemigo
Enemy::Enemy(float health, float speed, float arrowRes, float magicRes, float artilleryRes)
    : health(health), speed(speed),                                // *Inicializa salud y velocidad*
      arrowResistance(arrowRes), magicResistance(magicRes),        // *Inicializa resistencias a ataques*
      artilleryResistance(artilleryRes),
      position(0.f, 0.f) {}                                        // *Inicializa la posición en (0,0)*

// 💥 Aplica daño al enemigo según el tipo de ataque recibido
void Enemy::takeDamage(float amount, const std::string& damageType) {
    // 👉 Comprobar si el enemigo es Harpy y el daño es de artillería
    if (damageType == "artillery" && dynamic_cast<Harpy*>(this)) {
        std::cout << "🛡️ Harpy es inmune a la artillería\n";
        return; // ❌ No recibe daño
    }

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
        health = 0.f;
    }
}


// 📏 Devuelve la salud actual del enemigo
float Enemy::getHealth() const {
    return health;
}

// 📍 Devuelve la posición actual del enemigo
sf::Vector2f Enemy::getPosition() const {
    return position;
}
