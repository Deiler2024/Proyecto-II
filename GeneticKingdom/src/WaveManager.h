#pragma once
#include <queue>
#include "Enemy.h"
#include "Ogre.h"
#include "DarkElf.h"
#include "Harpy.h"
#include "Mercenary.h"

class WaveManager {
private:
    int waveNumber = 0;
    float spawnTimer = 0.f;
    float spawnInterval = 1.0f; // Tiempo entre spawns
    std::queue<Enemy*> pendingEnemies;
    sf::Vector2i spawnPoint;
    sf::Vector2i goalPoint;
    std::vector<std::vector<int>> mapLayout;

public:
    WaveManager(const sf::Vector2i& spawn, const sf::Vector2i& goal, const std::vector<std::vector<int>>& layout);

    void update(float deltaTime, std::vector<Enemy*>& enemies);
    bool hasPendingEnemies() const;
    void generateNextWave();
};
