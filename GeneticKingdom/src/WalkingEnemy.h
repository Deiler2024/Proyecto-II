// WalkingEnemy.h
#pragma once                                     // *Evita inclusiones múltiples del mismo archivo*
#include "Enemy.h"                              // *Incluye la clase base Enemy*
#include "AStar.h"                              // *Incluye funciones para pathfinding (A*)*
#include <vector>                               // *Incluye std::vector para almacenar el camino*

class WalkingEnemy : public Enemy {             // *Clase derivada de Enemy para enemigos que caminan*
protected:
    std::vector<sf::Vector2i> path;              // *Vector que almacena el camino como una serie de celdas (posiciones)*
    int currentPathIndex = 0;                     // *Índice del siguiente punto del camino al que se dirige el enemigo*
    float moveSpeed;                              // *Velocidad de movimiento del enemigo en pixeles por segundo*

public:
    WalkingEnemy(float health, float moveSpeed, // *Constructor que inicializa atributos del enemigo y genera el camino*
                 float arrowRes, float magicRes, float artilleryRes,
                 const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell,
                 const std::vector<std::vector<int>>& mapLayout);

    void moveAlongPath(float deltaTime);         // *Método para mover al enemigo a lo largo del camino, actualizado cada frame*
};
