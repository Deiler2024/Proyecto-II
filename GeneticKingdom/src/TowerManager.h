#pragma once

#include "Tile.h"               // *Declaración de Tile y TileType*
#include "Enemy.h"              // *Declaración base de Enemy*
#include <SFML/Graphics.hpp>    // *SFML para gráficos y vectores*
#include <vector>               // *Uso de std::vector para contenedores*
#include "Projectile.h"         // *Clase Projectile para disparos*

// Estructura que representa una torre en el juego
struct Tower {
    sf::Vector2f position;        // *Posición en el mapa (coordenadas en pixeles)*
    TileType type;                // *Tipo de torre (arquero, mago, artillería)*
    float range;                  // *Radio de alcance para detectar enemigos*
    float damage;                 // *Daño que inflige la torre*
    float fireCooldown;           // *Tiempo entre disparos*
    float fireTimer;              // *Temporizador para controlar disparos*
};

// Clase que administra todas las torres y sus proyectiles
class TowerManager {
private:
    sf::Texture arrowTexture;        // *Textura para proyectiles de tipo flecha*
    sf::Texture fireTexture;         // *Textura para proyectiles mágicos*
    sf::Texture cannonballTexture;   // *Textura para proyectiles de artillería*

    std::vector<Tower> towers;           // *Contenedor de torres construidas*
    std::vector<Projectile> projectiles; // *Contenedor de proyectiles activos*

public:
    TowerManager();                  // *Constructor: carga texturas para proyectiles*
    void addTower(const sf::Vector2f& pos, TileType type);  // *Agregar torre nueva*
    void update(float deltaTime, std::vector<Enemy*>& enemies); // *Actualizar torres y proyectiles*
    void draw(sf::RenderWindow& window);                      // *Dibujar torres y proyectiles*
    void upgradeTowerAt(const sf::Vector2f& pos);             // *Mejorar torre en posición dada*
    void removeTowerAt(const sf::Vector2f& pos); // 👈 Añadir esta línea en la sección public

};
