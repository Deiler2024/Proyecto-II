#pragma once // Asegura que este archivo de encabezado solo se incluya una vez

#include "Enemy.h"               // Clase base abstracta Enemy
#include "AStar.h"               // Algoritmo de búsqueda de caminos
#include <SFML/Graphics.hpp>     // Biblioteca para gráficos 2D
#include <vector>                // Contenedor para manejar listas
#include "WalkingEnemy.h"        // Clase base para enemigos que caminan

// Clase Ogre: representa a un enemigo tipo ogro que camina
class Ogre : public WalkingEnemy {
private:
    static sf::Texture texture;       // Textura estática compartida entre todos los ogros
    static bool textureLoaded;        // Indica si la textura ya fue cargada
    sf::Sprite sprite;                // Sprite visual del ogro

public:
    // Constructor que recibe punto de inicio, punto objetivo y diseño del mapa
    Ogre(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout);

    void update(float deltaTime) override;                  // Actualiza movimiento del ogro
    void draw(sf::RenderWindow& window) override;           // Dibuja al ogro en la ventana
    int getReward() const override;                         // Recompensa en monedas al ser derrotado
};

