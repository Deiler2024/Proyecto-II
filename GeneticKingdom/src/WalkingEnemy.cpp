// WalkingEnemy.cpp
#include "WalkingEnemy.h"             // *Incluye la definición de WalkingEnemy*
#include <cmath>                     // *Para funciones matemáticas como sqrt*

// Constructor de WalkingEnemy que recibe atributos y genera el camino a seguir
WalkingEnemy::WalkingEnemy(float health, float moveSpeed,          // *Inicializa atributos básicos: vida y velocidad*
                           float arrowRes, float magicRes, float artilleryRes, // *Resistencias*
                           const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, // *Punto de inicio y destino*
                           const std::vector<std::vector<int>>& mapLayout)           // *Mapa para encontrar camino*
    : Enemy(health, moveSpeed, arrowRes, magicRes, artilleryRes),   // *Inicializa la clase base Enemy*
      moveSpeed(moveSpeed)                                          // *Inicializa la velocidad de movimiento*
{
    path = findPath(spawnCell, castleCell, mapLayout);              // *Calcula el camino usando A* desde spawn a castillo*
    currentPathIndex = 0;                                            // *Empieza en el primer punto del camino*

    if (!path.empty()) {                                             // *Si el camino no está vacío*
        position = sf::Vector2f(path[0].x * 50.f, path[0].y * 50.f); // *Posiciona al enemigo en la primera celda del camino (50 = tamaño tile)*
    }
}

// Método para mover el enemigo a lo largo del camino
void WalkingEnemy::moveAlongPath(float deltaTime) {
    if (path.empty() || currentPathIndex >= path.size())             // *Si no hay camino o ya llegó al final, no hace nada*
        return;

    sf::Vector2f target(path[currentPathIndex].x * 50.f, path[currentPathIndex].y * 50.f); // *Posición objetivo actual en pixeles*
    sf::Vector2f direction = target - position;                      // *Vector dirección hacia el objetivo*

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y); // *Calcula distancia al objetivo*

    if (distance < 2.f) {                                            // *Si está suficientemente cerca del objetivo*
        position = target;                                           // *Posición exacta en el objetivo*
        currentPathIndex++;                                          // *Avanza al siguiente punto del camino*
    } else {
        sf::Vector2f movement = (direction / distance) * moveSpeed * deltaTime; // *Calcula movimiento proporcional a velocidad y tiempo*
        position += movement;                                        // *Actualiza posición sumando el movimiento*
    }
}
