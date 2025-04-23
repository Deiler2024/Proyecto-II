#pragma once
#include "Tile.h"
#include <vector>

class Map {
public:
    Map(int rows, int cols, float tileSize);

    void draw(sf::RenderWindow& window) const;
    void setTileType(int row, int col, TileType type);
    void handleClick(float mouseX, float mouseY, TileType type);


private:
    int rows, cols;
    float tileSize;
    std::vector<std::vector<Tile>> grid;
};
