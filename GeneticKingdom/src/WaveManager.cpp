#include "WaveManager.h"
#include <random>

WaveManager::WaveManager(const sf::Vector2i& spawn, const sf::Vector2i& goal, const std::vector<std::vector<int>>& layout)
    : spawnPoint(spawn), goalPoint(goal), mapLayout(layout) {
    generateNextWave(); // Generar la primera oleada
}

void WaveManager::update(float deltaTime, std::vector<Enemy*>& enemies) {
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval && !pendingEnemies.empty()) {
        Enemy* next = pendingEnemies.front();
        pendingEnemies.pop();
        enemies.push_back(next);
        spawnTimer = 0.f;
    }

    // Si ya no hay enemigos pendientes y tampoco enemigos vivos, generamos la siguiente oleada
    if (pendingEnemies.empty() && enemies.empty()) {
        generateNextWave();
    }
}

bool WaveManager::hasPendingEnemies() const {
    return !pendingEnemies.empty();
}

void WaveManager::generateNextWave() {
    waveNumber++;

    int totalEnemies = 4 + waveNumber; // 📈 Más enemigos cada oleada

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> enemyType(0, 3); // 0=Ogre, 1=DarkElf, 2=Harpy, 3=Mercenary

    for (int i = 0; i < totalEnemies; ++i) {
        int type = enemyType(gen);
        switch (type) {
            case 0:
                pendingEnemies.push(new Ogre(spawnPoint, goalPoint, mapLayout));
                break;
            case 1:
                pendingEnemies.push(new DarkElf(spawnPoint, goalPoint, mapLayout));
                break;
            case 2:
                pendingEnemies.push(new Harpy(spawnPoint, goalPoint, mapLayout));
                break;
            case 3:
                pendingEnemies.push(new Mercenary(spawnPoint, goalPoint, mapLayout));
                break;
        }
    }
}
