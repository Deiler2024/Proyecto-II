// Harpy.h
#pragma once
#include "WalkingEnemy.h"
#include <SFML/Graphics.hpp>

class Harpy : public WalkingEnemy {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;

public:
    Harpy(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    int getReward() const override; // 👈 Añadido aquí
};
