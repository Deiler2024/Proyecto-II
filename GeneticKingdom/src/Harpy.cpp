// Harpy.cpp
#include "Harpy.h"
#include "WalkingEnemy.h"


sf::Texture Harpy::texture;
bool Harpy::textureLoaded = false;

Harpy::Harpy(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(60.f, 100.f, 0.5f, 0.5f, 0.0f, spawnCell, castleCell, mapLayout) // Vida, velocidad, resistencias
{
    if (!textureLoaded) {
        if (!texture.loadFromFile("./harpy.png")) {
            throw std::runtime_error("Error cargando harpy.png");
        }
        textureLoaded = true;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.9f, 0.9f);
}

void Harpy::update(float deltaTime) {
    moveAlongPath(deltaTime);
}

void Harpy::draw(sf::RenderWindow& window) {
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

int Harpy::getReward() const {
    return 12;
}
