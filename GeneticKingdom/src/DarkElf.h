// DarkElf.h
#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "AStar.h"
#include "WalkingEnemy.h"


class DarkElf : public WalkingEnemy {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;

public:
    DarkElf(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
