#pragma once
#include "Enemy.h"
#include "AStar.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Ogre : public Enemy {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;

    std::vector<sf::Vector2i> path; // 🛣️ Camino que seguirá (en celdas)
    int currentPathIndex = 0;        // Índice actual dentro del camino
    float moveSpeed = 50.f;           // Velocidad de movimiento (pixeles por segundo)

public:
    Ogre(const sf::Vector2i& startCell, const sf::Vector2i& goalCell, const std::vector<std::vector<int>>& mapLayout);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
