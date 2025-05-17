#pragma once  // *Evita inclusiones múltiples del mismo archivo*

#include "Tile.h"  // *Incluye la definición de la clase Tile*
#include <vector>   // *Incluye el contenedor vector*

class Map {
public:
    Map(int rows, int cols, float tileSize);  // *Constructor que recibe filas, columnas y tamaño de cada tile*

    void draw(sf::RenderWindow& window) const;  // *Función para dibujar el mapa en la ventana SFML*
    void setTileType(int row, int col, TileType type);  // *Establece el tipo de tile en la posición dada*
    void handleClick(float mouseX, float mouseY, TileType type);  // *Maneja la interacción del mouse para modificar tiles*

private:
    int rows, cols;  // *Número de filas y columnas del mapa*
    float tileSize;  // *Tamaño (ancho/alto) de cada tile en pixeles*
    std::vector<std::vector<Tile>> grid;  // *Matriz 2D de tiles que representa el mapa*
};

