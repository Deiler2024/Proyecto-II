// DarkElf.cpp
#include "DarkElf.h"
#include "AStar.h"
#include "WalkingEnemy.h"


sf::Texture DarkElf::texture;
bool DarkElf::textureLoaded = false;

DarkElf::DarkElf(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(80.f, 130.f, 0.5f, 0.8f, 0.5f, spawnCell, castleCell, mapLayout) // Vida, velocidad, resistencias
{
    if (!textureLoaded) {
        if (!texture.loadFromFile("./darkelf.png")) {
            throw std::runtime_error("Error cargando darkelf.png");
        }
        textureLoaded = true;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.8f, 0.8f);
}

void DarkElf::update(float deltaTime) {
    moveAlongPath(deltaTime);
}

void DarkElf::draw(sf::RenderWindow& window) {
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
