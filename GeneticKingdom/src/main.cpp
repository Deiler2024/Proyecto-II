#include "Map.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Genetic Kingdom");
    window.setFramerateLimit(60);

    const int rows = 12;
    const int cols = 16;
    const float tileSize = 50.0f;

    Map gameMap(rows, cols, tileSize);

    // 🧱 Matriz de diseño: 1 = puente, 0 = vacío
    std::vector<std::vector<int>> mapLayout = {
        {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}, // (0,0) inicio
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, // baja a la derecha
        {0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0}, // gira hacia abajo
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}, // sube a la izquierda
        {0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // gira hacia abajo
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // sube a la derecha
        {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1}, // gira hacia abajo
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // sube a la izquierda
        {1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0}, // gira hacia abajo
        {1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0}, // sube a la derecha
        {0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0}, // gira hacia abajo
        {0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0} // sube a la izquierda
        
    };

    // 🏗️ Construir el mapa a partir de la matriz
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (mapLayout[row][col] == 1) {
                gameMap.setTileType(row, col, TileType::Bridge);
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            // 🖱️ Click izquierdo: colocar torre
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;
                gameMap.handleClick(mouseX, mouseY, TileType::Tower);
            }

            // 🖱️ Click derecho: limpiar celda (Empty)
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;
                gameMap.handleClick(mouseX, mouseY, TileType::Empty);
            }
        }

        window.clear();
        gameMap.draw(window);
        window.display();
    }

    return 0;
}
