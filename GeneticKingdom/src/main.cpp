#include "Map.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    const int rows = 12;
    const int cols = 16;
    const float tileSize = 50.0f;
    const int menuWidth = 300; // 🆕 Espacio reservado para el menú

    sf::RenderWindow window(sf::VideoMode(cols * tileSize + menuWidth, rows * tileSize), "Genetic Kingdom");
    window.setFramerateLimit(60);

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

    // 🎯 Texturas de los botones
    sf::Texture archerTexture, mageTexture, artilleryTexture;

        // Cargar imágenes desde la carpeta actual
        if (!archerTexture.loadFromFile("./archer.png")) {
            // Manejar error si la imagen no se carga
            std::cerr << "Error al cargar archer.png" << std::endl;
        }

        if (!mageTexture.loadFromFile("./mage.png")) {
            std::cerr << "Error al cargar mage.png" << std::endl;
        }

        if (!artilleryTexture.loadFromFile("./artillery.png")) {
            std::cerr << "Error al cargar artillery.png" << std::endl;
        }

    // 🎯 Botones
    float buttonSize = 80.0f;
    float buttonStartX = cols * tileSize + (menuWidth - buttonSize) / 2;

    Button archerButton(buttonStartX, 50, buttonSize, archerTexture);
    Button mageButton(buttonStartX, 150, buttonSize, mageTexture);
    Button artilleryButton(buttonStartX, 250, buttonSize, artilleryTexture);

    // Tipo de torre seleccionada (por defecto, arquero)
    TileType selectedTowerType = TileType::ArcherTower;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            // 🖱️ Click izquierdo
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;

                if (mouseX < cols * tileSize) {
                    // Click en el mapa
                    gameMap.handleClick(mouseX, mouseY, selectedTowerType);
                } else {
                    if (archerButton.isClicked(mouseX, mouseY)) {
                        selectedTowerType = TileType::ArcherTower;
                    } else if (mageButton.isClicked(mouseX, mouseY)) {
                        selectedTowerType = TileType::MageTower;
                    } else if (artilleryButton.isClicked(mouseX, mouseY)) {
                        selectedTowerType = TileType::ArtilleryTower;
                    }
                    
                }
            }

            // 🖱️ Click derecho: limpiar casilla
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;

                if (mouseX < cols * tileSize) {
                    gameMap.handleClick(mouseX, mouseY, TileType::Empty);
                }
            }
        }

        window.clear();
        gameMap.draw(window);

        // 🎨 Dibujar fondo del menú
        sf::RectangleShape menuBackground(sf::Vector2f(menuWidth, rows * tileSize));
        menuBackground.setPosition(cols * tileSize, 0);
        menuBackground.setFillColor(sf::Color(200, 200, 200));
        window.draw(menuBackground);

        // 🎨 Dibujar botones
        archerButton.draw(window);
        mageButton.draw(window);
        artilleryButton.draw(window);

        window.display();
    }

    return 0;
}