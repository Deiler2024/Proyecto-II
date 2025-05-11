// Mercenary.cpp
#include "Mercenary.h"
#include <cmath>
#include <iostream>
#include "WalkingEnemy.h"



sf::Texture Mercenary::texture;
bool Mercenary::textureLoaded = false;

Mercenary::Mercenary(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(90.f, 70.f, 0.1f, 0.9f, 0.1f, spawnCell, castleCell, mapLayout) // Vida, velocidad, resistencias
{
    if (!textureLoaded) {
        if (!texture.loadFromFile("./mercenary.png")) {
            std::cerr << "Error cargando mercenary.png" << std::endl;
            throw std::runtime_error("Error al cargar mercenary.png");
        } else {
            std::cout << "Mercenary texture loaded correctly!\n"; // ✅
        }
        textureLoaded = true;
    }
    
    sprite.setTexture(texture);
    sprite.setScale(0.9f, 0.9f);
}

void Mercenary::update(float deltaTime) {
    moveAlongPath(deltaTime);
}

void Mercenary::draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);

    float lifePercent = health / 100.f;
    if (lifePercent > 0.f) {
        sf::RectangleShape lifeBarBg(sf::Vector2f(40.f, 5.f));
        lifeBarBg.setFillColor(sf::Color::Red);
        lifeBarBg.setPosition(position.x, position.y - 10.f);

        sf::RectangleShape lifeBar(sf::Vector2f(40.f * lifePercent, 5.f));
        lifeBar.setFillColor(sf::Color::Green);
        lifeBar.setPosition(position.x, position.y - 10.f);

        window.draw(lifeBarBg);
        window.draw(lifeBar);
    }
}
