#pragma once
#include <SFML/Graphics.hpp>

enum class TileType {
    Empty,
    Bridge,
    ArcherTower,   // 🏹
    MageTower,     // 🔮
    ArtilleryTower // 💣
};

class Tile {
public:
    Tile(float x, float y, float size);

    void setType(TileType type);
    TileType getType() const;

    void draw(sf::RenderWindow& window) const;

private:
    TileType type;
    sf::RectangleShape shape;
};
