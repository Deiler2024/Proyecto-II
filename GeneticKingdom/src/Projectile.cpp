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
    if (!active) return; // Si el proyectil ya no está activo, no hacer nada

    if (target) {
        // 🔍 Calcular dirección hacia el objetivo
        sf::Vector2f dir = target->getPosition() - sprite.getPosition();
        float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        // 🎯 Si está cerca del objetivo, aplicar daño y desactivar
        if (distance < 20.f) {
            target->takeDamage(damage, damageType); // Aplica daño al objetivo
            active = false;                         // Desactiva el proyectil
            return;
        }

        // ➡️ Mover hacia el objetivo
        sf::Vector2f movement = (dir / distance) * speed * deltaTime;
        sprite.move(movement);
    } else {
        // 🛫 Si no hay objetivo, simplemente mover hacia la derecha
        sprite.move(speed * deltaTime, 0.f);

        // 🚫 Eliminar si sale de pantalla
        if (sprite.getPosition().x > 1300) {
            active = false;
        }
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
