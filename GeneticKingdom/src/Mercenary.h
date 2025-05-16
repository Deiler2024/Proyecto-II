#pragma once // 🛡️ Asegura que el archivo se incluya solo una vez en la compilación

// Mercenary.h

#include "Enemy.h"            // Clase base Enemy con atributos generales
#include "AStar.h"            // Algoritmo de pathfinding
#include <SFML/Graphics.hpp>  // Librería SFML para gráficos
#include <vector>             // Contenedor std::vector
#include "WalkingEnemy.h"     // Clase base para enemigos que se mueven caminando


// 📦 Clase Mercenary que representa un enemigo mercenario en el juego
class Mercenary : public WalkingEnemy { // Hereda comportamiento de WalkingEnemy
private:
    static sf::Texture texture;       // Textura compartida por todas las instancias
    static bool textureLoaded;        // Marca si la textura fue cargada
    sf::Sprite sprite;                // Sprite que representa al mercenario

public:
    // 🏗️ Constructor: recibe celda de inicio, meta y layout del mapa
    Mercenary(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout);

    // 🔄 Actualiza la posición del mercenario
    void update(float deltaTime) override;

    // 🎨 Dibuja el sprite del mercenario en pantalla
    void draw(sf::RenderWindow& window) override;

    // 💰 Devuelve las monedas que se obtienen al derrotar al mercenario
    int getReward() const override;
};
