#include "TowerManager.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdexcept> // Para std::runtime_error


TowerManager::TowerManager() {
    // Intentar cargar texturas con manejo de errores
    if (!arrowTexture.loadFromFile("./flecha.png")) {
        std::cerr << "Error crítico: No se pudo cargar la textura './flecha.png'\n";
        throw std::runtime_error("Fallo al cargar recurso: flecha.png");
    }

    if (!fireTexture.loadFromFile("./fuego.png")) {
        std::cerr << "Error crítico: No se pudo cargar la textura './fuego.png'\n";
        throw std::runtime_error("Fallo al cargar recurso: fuego.png");
    }

    if (!cannonballTexture.loadFromFile("./bala.png")) {
        std::cerr << "Error crítico: No se pudo cargar la textura './bala.png'\n";
        throw std::runtime_error("Fallo al cargar recurso: balas.png");
    }

    // Texturas cargadas con éxito
    std::cout << "Todas las texturas se cargaron correctamente.\n";
}

void TowerManager::addTower(const sf::Vector2f& pos, TileType type) {
    Tower tower;
    tower.position = pos;
    tower.type = type;
    tower.fireTimer = 0.f;

    switch (type) {
        case TileType::ArcherTower:
            tower.range = 150.f;
            tower.damage = 20.f;
            tower.fireCooldown = 1.f;
            break;
        case TileType::MageTower:
            tower.range = 200.f;
            tower.damage = 35.f;
            tower.fireCooldown = 1.5f;
            break;
        case TileType::ArtilleryTower:
            tower.range = 250.f;
            tower.damage = 50.f;
            tower.fireCooldown = 2.f;
            break;
        default:
            break;
    }

    towers.push_back(tower);
}

void TowerManager::update(float deltaTime, std::vector<Enemy*>& enemies) {
    for (Tower& tower : towers) {
        tower.fireTimer += deltaTime;

        if (tower.fireTimer >= tower.fireCooldown) {
            Enemy* closestEnemy = nullptr;
            float closestDistance = tower.range; // Solo buscar dentro del rango

            // 🔍 Buscar el enemigo más cercano dentro del rango
            for (Enemy* enemy : enemies) {
                sf::Vector2f toEnemy = enemy->getPosition() - tower.position;
                float distance = std::sqrt(toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y);

                if (distance <= tower.range && distance < closestDistance) {
                    closestDistance = distance;
                    closestEnemy = enemy;
                }
            }

            if (closestEnemy) {
                // Crear proyectil hacia el enemigo más cercano
                sf::Texture* projTexture = nullptr;
                std::string damageType = "arrow";

                if (tower.type == TileType::ArcherTower) {
                    projTexture = &arrowTexture;
                    damageType = "arrow";
                } else if (tower.type == TileType::MageTower) {
                    projTexture = &fireTexture;
                    damageType = "magic";
                } else if (tower.type == TileType::ArtilleryTower) {
                    projTexture = &cannonballTexture;
                    damageType = "artillery";
                }

                if (projTexture) {
                    projectiles.emplace_back(
                        tower.position, closestEnemy,
                        300.f, // Velocidad del proyectil
                        tower.damage,
                        damageType,
                        *projTexture
                    );
                }

                tower.fireTimer = 0.f;
            }
        }
    }

    // 🔄 Actualizar proyectiles
    for (auto& proj : projectiles) {
        proj.update(deltaTime);
    }

    // 🧹 Eliminar proyectiles inactivos
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p) {
            return !p.isActive();
        }),
        projectiles.end()
    );
}



void TowerManager::draw(sf::RenderWindow& window) {
    for (const Tower& tower : towers) {
        sf::CircleShape rangeCircle;
        rangeCircle.setRadius(tower.range);
        rangeCircle.setOrigin(tower.range, tower.range);
        rangeCircle.setPosition(tower.position);
        rangeCircle.setFillColor(sf::Color(0, 0, 0, 0));
        rangeCircle.setOutlineThickness(1.f);
        rangeCircle.setOutlineColor(sf::Color::Green);
        window.draw(rangeCircle);
    }

    for (const auto& proj : projectiles) {
        proj.draw(window);
    }
}
