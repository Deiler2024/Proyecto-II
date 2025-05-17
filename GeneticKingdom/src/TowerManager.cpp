#include "TowerManager.h"                 // *Incluye la declaración de TowerManager y dependencias*
#include <cmath>                         // *Para funciones matemáticas (sqrt, etc.)*
#include <algorithm>                     // *Para std::remove_if*
#include <iostream>                      // *Para imprimir mensajes en consola*
#include <stdexcept>                    // *Para lanzar excepciones estándar*


TowerManager::TowerManager() {
    // Intentar cargar texturas con manejo de errores
    if (!arrowTexture.loadFromFile("./flecha.png")) {                    // *Cargar textura para proyectiles de flechas*
        std::cerr << "Error crítico: No se pudo cargar la textura './flecha.png'\n";
        throw std::runtime_error("Fallo al cargar recurso: flecha.png"); // *Si falla, lanzar excepción para detener programa*
    }

    if (!fireTexture.loadFromFile("./fuego.png")) {                      // *Cargar textura para proyectiles mágicos*
        std::cerr << "Error crítico: No se pudo cargar la textura './fuego.png'\n";
        throw std::runtime_error("Fallo al cargar recurso: fuego.png");  // *Misma lógica para error*
    }

    if (!cannonballTexture.loadFromFile("./bala.png")) {                 // *Cargar textura para proyectiles de artillería*
        std::cerr << "Error crítico: No se pudo cargar la textura './bala.png'\n";
        throw std::runtime_error("Fallo al cargar recurso: balas.png");  // *Misma lógica para error*
    }

    // Texturas cargadas con éxito
    std::cout << "Todas las texturas se cargaron correctamente.\n";     // *Mensaje informativo*
}

void TowerManager::addTower(const sf::Vector2f& pos, TileType type) {
    Tower tower;                          // *Crear nueva torre*
    tower.position = pos;                 // *Asignar posición*
    tower.type = type;                   // *Asignar tipo de torre*
    tower.fireTimer = 0.f;               // *Inicializar temporizador de disparo*

    // Establecer atributos según tipo de torre
    switch (type) {
        case TileType::ArcherTower:
            tower.range = 150.f;          // *Rango de ataque*
            tower.damage = 20.f;          // *Daño por disparo*
            tower.fireCooldown = 1.f;     // *Tiempo entre disparos*
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
            break;                       // *No hacer nada si tipo desconocido*
    }

    towers.push_back(tower);              // *Agregar torre al vector de torres*
}

void TowerManager::update(float deltaTime, std::vector<Enemy*>& enemies) {
    for (Tower& tower : towers) {        // *Iterar sobre todas las torres*
        tower.fireTimer += deltaTime;    // *Incrementar temporizador*

        if (tower.fireTimer >= tower.fireCooldown) {  // *Si pasó tiempo suficiente para disparar*
            Enemy* closestEnemy = nullptr;
            float closestDistance = tower.range;      // *Inicializar búsqueda con rango máximo*

            // Buscar enemigo más cercano dentro del rango
            for (Enemy* enemy : enemies) {
                sf::Vector2f toEnemy = enemy->getPosition() - tower.position;    // *Vector hacia enemigo*
                float distance = std::sqrt(toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y); // *Distancia Euclidiana*

                if (distance <= tower.range && distance < closestDistance) {   // *Si está dentro del rango y es más cercano*
                    closestDistance = distance;    // *Actualizar distancia más corta*
                    closestEnemy = enemy;          // *Actualizar objetivo*
                }
            }

            if (closestEnemy) {    // *Si se encontró enemigo válido*
                // Preparar proyectil según tipo de torre
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

                if (projTexture) {   // *Si textura válida, crear proyectil*
                    projectiles.emplace_back(
                        tower.position, closestEnemy,
                        300.f,             // *Velocidad del proyectil*
                        tower.damage,
                        damageType,
                        *projTexture
                    );
                }

                tower.fireTimer = 0.f;    // *Resetear temporizador para nuevo disparo*
            }
        }
    }

    // Actualizar todos los proyectiles
    for (auto& proj : projectiles) {
        proj.update(deltaTime);
    }

    // Eliminar proyectiles inactivos (los que impactaron o salieron)
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
        rangeCircle.setRadius(tower.range);                    // *Radio del círculo es el rango de la torre*
        rangeCircle.setOrigin(tower.range, tower.range);       // *Centrar el círculo en la posición*
        rangeCircle.setPosition(tower.position);               // *Colocar círculo en la posición de la torre*
        rangeCircle.setFillColor(sf::Color(0, 0, 0, 0));       // *Fondo transparente*
        rangeCircle.setOutlineThickness(1.f);                   // *Grosor del borde*
        rangeCircle.setOutlineColor(sf::Color::Green);          // *Color del borde*
        window.draw(rangeCircle);                               // *Dibujar círculo en ventana*
    }

    // Dibujar todos los proyectiles activos
    for (const auto& proj : projectiles) {
        proj.draw(window);
    }
}

// Mejorar torre en posición dada aumentando daño
void TowerManager::upgradeTowerAt(const sf::Vector2f& pos) {
    for (Tower& tower : towers) {
        if (tower.position == pos) {           // *Si la torre está en la posición dada*
            tower.damage += 10.f;               // *Aumentar daño en 10*
            std::cout << "🔧 Torre mejorada en " << pos.x << ", " << pos.y << std::endl; // *Mensaje consola*
            break;                            // *Terminar búsqueda después de mejorar*
        }
    }
}

void TowerManager::removeTowerAt(const sf::Vector2f& pos) {
    towers.erase(std::remove_if(towers.begin(), towers.end(), [&](const Tower& t) {
        return t.position == pos;
    }), towers.end());
}



