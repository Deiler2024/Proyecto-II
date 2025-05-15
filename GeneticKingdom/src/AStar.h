#pragma once // *Evita inclusiones múltiples del archivo durante la compilación*

#include <vector> // *Incluye soporte para std::vector*
#include <SFML/Graphics.hpp> // *Incluye tipos gráficos de SFML, como sf::Vector2i*

// *Declara la función que implementa el algoritmo A* para encontrar un camino entre dos puntos*
std::vector<sf::Vector2i> findPath(
    const sf::Vector2i& start, // *Posición inicial en el mapa (columna, fila)*
    const sf::Vector2i& goal, // *Destino en el mapa (columna, fila)*
    const std::vector<std::vector<int>>& mapLayout // *Matriz del mapa con los tipos de celdas*
);

