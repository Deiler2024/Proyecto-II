// WalkingEnemy.cpp
#include "WalkingEnemy.h"
#include <cmath>

WalkingEnemy::WalkingEnemy(float health, float moveSpeed,
                           float arrowRes, float magicRes, float artilleryRes,
                           const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell,
                           const std::vector<std::vector<int>>& mapLayout)
    : Enemy(health, moveSpeed, arrowRes, magicRes, artilleryRes),
      moveSpeed(moveSpeed)
{
    path = findPath(spawnCell, castleCell, mapLayout);
    currentPathIndex = 0;

    if (!path.empty()) {
        position = sf::Vector2f(path[0].x * 50.f, path[0].y * 50.f);
    }
}

void WalkingEnemy::moveAlongPath(float deltaTime) {
    if (path.empty() || currentPathIndex >= path.size())
        return;

    sf::Vector2f target(path[currentPathIndex].x * 50.f, path[currentPathIndex].y * 50.f);
    sf::Vector2f direction = target - position;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 2.f) {
        position = target;
        currentPathIndex++;
    } else {
        sf::Vector2f movement = (direction / distance) * moveSpeed * deltaTime;
        position += movement;
    }
}
