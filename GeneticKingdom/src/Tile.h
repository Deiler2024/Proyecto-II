#pragma once // 🔒 Asegura que este archivo solo se incluya una vez durante la compilación

#include <SFML/Graphics.hpp> // 🎮 Librería para gráficos y ventanas

// 📦 Enumeración que define los tipos posibles de tile en el mapa
enum class TileType {
    Empty,           // ⬜ Casilla vacía
    Bridge,          // 🌉 Camino por donde caminan los enemigos
    ArcherTower,     // 🏹 Torre de arqueros
    MageTower,       // 🔮 Torre mágica
    ArtilleryTower   // 💣 Torre de artillería
};

// 🧱 Clase que representa una casilla del mapa
class Tile {
public:
    Tile(float x, float y, float size); // 🏗️ Constructor con posición y tamaño

    void setType(TileType type);             // 🔁 Cambia el tipo del tile
    TileType getType() const;                // 🔍 Obtiene el tipo actual del tile

    void draw(sf::RenderWindow& window) const; // 🖼️ Dibuja el tile en la ventana

private:
    TileType type;                 // 🧭 Tipo actual del tile
    sf::RectangleShape shape;      // 🔲 Forma del tile (usada para dibujar y posicionar)
};
