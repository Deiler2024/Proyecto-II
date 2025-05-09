#pragma once
#include "Tile.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"


struct Tower {
    sf::Vector2f position;
    TileType type;
    float range;
    float damage;
    float fireCooldown;
    float fireTimer;
};

class TowerManager {
private:
    sf::Texture arrowTexture;
    sf::Texture fireTexture;
    sf::Texture cannonballTexture;
    std::vector<Tower> towers;
    std::vector<Projectile> projectiles;

public:
    TowerManager(); // <-- Constructor que carga imágenes
    void addTower(const sf::Vector2f& pos, TileType type);
    void update(float deltaTime, std::vector<Enemy*>& enemies);
    void draw(sf::RenderWindow& window);
};