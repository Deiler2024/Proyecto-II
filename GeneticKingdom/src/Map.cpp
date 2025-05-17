#include "Map.h"  // *Incluye la declaración de la clase Map*

Map::Map(int rows, int cols, float tileSize)  // *Constructor de Map con filas, columnas y tamaño de cada tile*
    : rows(rows), cols(cols), tileSize(tileSize)  // *Inicializa los atributos con los valores recibidos*
{
    grid.resize(rows, std::vector<Tile>());  // *Redimensiona la grilla para tener 'rows' filas*
    for (int i = 0; i < rows; ++i) {  // *Itera sobre cada fila*
        for (int j = 0; j < cols; ++j) {  // *Itera sobre cada columna*
            grid[i].emplace_back(j * tileSize, i * tileSize, tileSize);  // *Agrega un tile en la posición correspondiente con tamaño tileSize*
        }
    }
}

void Map::draw(sf::RenderWindow& window) const {  // *Dibuja el mapa completo en la ventana*
    for (const auto& row : grid) {  // *Itera sobre cada fila*
        for (const auto& tile : row) {  // *Itera sobre cada tile en la fila*
            tile.draw(window);  // *Dibuja el tile en la ventana*
        }
    }
}

void Map::setTileType(int row, int col, TileType type) {  // *Establece el tipo de tile en la posición especificada*
    if (row >= 0 && row < rows && col >= 0 && col < cols)  // *Verifica que las coordenadas estén dentro del mapa*
        grid[row][col].setType(type);  // *Cambia el tipo del tile*
}

void Map::handleClick(float mouseX, float mouseY, TileType type) {  // *Maneja la interacción de clic del mouse sobre el mapa*
    int col = mouseX / tileSize;  // *Calcula la columna del tile clickeado*
    int row = mouseY / tileSize;  // *Calcula la fila del tile clickeado*

    if (row >= 0 && row < rows && col >= 0 && col < cols) {  // *Verifica que el clic esté dentro del mapa*
        TileType currentType = grid[row][col].getType();  // *Obtiene el tipo actual del tile*

        // ❌ No se permite colocar NINGÚN tipo de torre sobre el puente
        if (currentType == TileType::Bridge &&
            (type == TileType::ArcherTower || type == TileType::MageTower || type == TileType::ArtilleryTower)) {
            return;  // *Ignora el clic si se intenta poner torre sobre puente*
        }

        grid[row][col].setType(type);  // *Establece el nuevo tipo para el tile clickeado*
    }
}


TileType Map::getTileType(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return grid[row][col].getType();
    }
    return TileType::Empty; // Valor por defecto si es inválido
}
