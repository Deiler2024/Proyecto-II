#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <string>

class Projectile {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float speed;
    float damage;
    Enemy* target;
    std::string damageType;
    bool active;

public:
    Projectile(const sf::Vector2f& startPos, Enemy* target, float speed, float damage, const std::string& damageType, sf::Texture& texture);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isActive() const;
};

