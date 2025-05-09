#include "Projectile.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(const sf::Vector2f& startPos, Enemy* target, float speed, float damage, const std::string& damageType, sf::Texture& texture)
    : target(target), speed(speed), damage(damage), damageType(damageType), active(true)
{
    sprite.setTexture(texture);
    sprite.setPosition(startPos);

    // 🔥 Para prueba: No escalar pequeño, dejarlo tamaño original
    sprite.setScale(2.f, 2.f);

    std::cout << "Se creó un projectile en " << startPos.x << ", " << startPos.y << std::endl;
}

void Projectile::update(float deltaTime) {
    if (!active) return;

    if (target) {
        // 🎯 Si hay objetivo, seguirlo
        sf::Vector2f dir = target->getPosition() - sprite.getPosition();
        float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (distance < 20.f) {
            target->takeDamage(damage, damageType);
            active = false;
            return;
        }

        sf::Vector2f movement = (dir / distance) * speed * deltaTime;
        sprite.move(movement);
    } else {
        // ➡️ SIN objetivo: mover a la derecha
        sprite.move(speed * deltaTime, 0.f);

        // ❗ Si se sale de la pantalla, eliminar
        if (sprite.getPosition().x > 1300) { // Ajusta según resolución
            active = false;
        }
    }
}

void Projectile::draw(sf::RenderWindow& window) const {
    if (active) {
        window.draw(sprite);
        std::cout << "Dibujando projectile en " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    }
}

bool Projectile::isActive() const {
    return active;
}
