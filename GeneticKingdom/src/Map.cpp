#include "Map.h"

Map::Map(int rows, int cols, float tileSize)
    : rows(rows), cols(cols), tileSize(tileSize)
{
    grid.resize(rows, std::vector<Tile>());
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i].emplace_back(j * tileSize, i * tileSize, tileSize);
        }
    }
}

void Map::draw(sf::RenderWindow& window) const {
    for (const auto& row : grid) {
        for (const auto& tile : row) {
            tile.draw(window);
        }
    }
}

void Map::setTileType(int row, int col, TileType type) {
    if (row >= 0 && row < rows && col >= 0 && col < cols)
        grid[row][col].setType(type);
}

void Map::handleClick(float mouseX, float mouseY, TileType type) {
    int col = mouseX / tileSize;
    int row = mouseY / tileSize;

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        TileType currentType = grid[row][col].getType();

        // ❌ No se permite colocar torres sobre el puente
        if (currentType == TileType::Bridge && type == TileType::Tower) {
            return;
        }

        grid[row][col].setType(type);
    }
}

