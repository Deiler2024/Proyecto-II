#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Ogre : public Enemy {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;

public:
    Ogre();
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};

