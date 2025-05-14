#include "Ogre.h"
#include <cmath>
#include "WalkingEnemy.h"



sf::Texture Ogre::texture;
bool Ogre::textureLoaded = false;


Ogre::Ogre(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(150.f, 50.f, 0.1f, 0.6f, 0.8f, spawnCell, castleCell, mapLayout)
{
    if (!textureLoaded) {
        if (!texture.loadFromFile("./ogre.png")) {
            throw std::runtime_error("Error cargando ogre.png");
        }
        textureLoaded = true;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.9f, 0.9f);
}

void Ogre::update(float deltaTime) {
    moveAlongPath(deltaTime);
}

void Ogre::draw(sf::RenderWindow& window) {
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



