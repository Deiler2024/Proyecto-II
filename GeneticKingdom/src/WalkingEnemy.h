// WalkingEnemy.h
#pragma once
#include "Enemy.h"
#include "AStar.h"
#include <vector>

class WalkingEnemy : public Enemy {
protected:
    std::vector<sf::Vector2i> path;
    int currentPathIndex = 0;
    float moveSpeed;

public:
    WalkingEnemy(float health, float moveSpeed,
                 float arrowRes, float magicRes, float artilleryRes,
                 const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell,
                 const std::vector<std::vector<int>>& mapLayout);

    void moveAlongPath(float deltaTime);
};
