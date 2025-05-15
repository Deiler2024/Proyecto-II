#pragma once
#include "Enemy.h"
#include "AStar.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "WalkingEnemy.h"


class Ogre : public WalkingEnemy {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;

public:
    Ogre(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    int getReward() const override;

    

};


