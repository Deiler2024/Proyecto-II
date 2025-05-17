#include "Projectile.h"              // Incluye la definición de la clase Projectile
#include <cmath>                     // Para funciones matemáticas como sqrt
#include <iostream>                  // Para debug (comentado más abajo)

// 🧨 Constructor del proyectil
Projectile::Projectile(const sf::Vector2f& startPos, Enemy* target, float speed, float damage, const std::string& damageType, sf::Texture& texture)
    : target(target), speed(speed), damage(damage), damageType(damageType), active(true) // Inicializa atributos
{
    sprite.setTexture(texture);     // Asigna la textura al sprite
    sprite.setPosition(startPos);   // Posiciona el proyectil donde se generó

    sprite.setScale(2.f, 2.f);      // Escala el sprite (puede ajustarse si es necesario)

    // std::cout << "Se creó un projectile en " << startPos.x << ", " << startPos.y << std::endl; // Mensaje de debug opcional
}

// 🔄 Actualiza la posición y comportamiento del proyectil
void Projectile::update(float deltaTime) {
    if (!active) return;

    if (!lostTarget && target && target->getHealth() > 0.f) {
        // 🎯 Seguir al objetivo mientras esté vivo
        sf::Vector2f dir = target->getPosition() - sprite.getPosition();
        float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        fallbackTargetPos = target->getPosition(); // 🔄 Actualizar última posición válida

        if (distance < 20.f) {
            target->takeDamage(damage, damageType);
            active = false;
            return;
        }

        sf::Vector2f movement = (dir / distance) * speed * deltaTime;
        sprite.move(movement);
    } else {
        // 🔀 Objetivo muerto o perdido: ir a última posición conocida
        lostTarget = true;

        sf::Vector2f dir = fallbackTargetPos - sprite.getPosition();
        float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (distance < 20.f) {
            active = false; // 🚫 Al llegar a la posición final, desaparecer
            return;
        }

        sf::Vector2f movement = (dir / distance) * speed * deltaTime;
        sprite.move(movement);
    }
}


// 🎨 Dibuja el proyectil si sigue activo
void Projectile::draw(sf::RenderWindow& window) const {
    if (active) {
        window.draw(sprite); // Renderiza el sprite
        // std::cout << "Dibujando projectile en " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl; // Debug opcional
    }
}

// 🔁 Verifica si el proyectil sigue en juego
bool Projectile::isActive() const {
    return active;
}
