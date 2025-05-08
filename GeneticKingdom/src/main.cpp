#include "Map.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Ogre.h"
#include <vector>


std::vector<Enemy*> enemies; // Lista global de enemigos

int main() {
    const int rows = 12;
    const int cols = 16;
    const float tileSize = 50.0f;
    const int menuWidth = 300; // 🆕 Espacio reservado para el menú

    sf::RenderWindow window(sf::VideoMode(cols * tileSize + menuWidth, rows * tileSize), "Genetic Kingdom");
    window.setFramerateLimit(60);

    sf::Clock clock; // 🕒 ¡Esto es importante!

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
        {0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,2} // sube a la izquierda
        
    };

    
    // 🎯 Texturas de los botones y del castillo
    sf::Texture archerTexture, mageTexture, artilleryTexture, castleTexture;

    // Cargar imágenes
    if (!archerTexture.loadFromFile("./archer.png")) {
        std::cerr << "Error al cargar archer.png" << std::endl;
    }
    if (!mageTexture.loadFromFile("./mage.png")) {
        std::cerr << "Error al cargar mage.png" << std::endl;
    }
    if (!artilleryTexture.loadFromFile("./artillery.png")) {
        std::cerr << "Error al cargar artillery.png" << std::endl;
    }
    if (!castleTexture.loadFromFile("./castle.png")) {
        std::cerr << "Error al cargar castle.png" << std::endl;
    }    
    // 📍 Posición del castillo
    sf::Vector2f castlePosition;

    // 🏗️ Construir el mapa a partir de la matriz y encontrar el castillo
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (mapLayout[row][col] == 1) {
                gameMap.setTileType(row, col, TileType::Bridge);
            } else if (mapLayout[row][col] == 2) {
                // Guardar la posición del castillo
                castlePosition = sf::Vector2f(col * tileSize, row * tileSize);
                gameMap.setTileType(row, col, TileType::Bridge); // Opcional: considerar como puente si quieres que caminen hacia él
            }
        }
    }

    // 🎯 Botones
    float buttonSize = 80.0f;
    float buttonStartX = cols * tileSize + (menuWidth - buttonSize) / 2;

    Button archerButton(buttonStartX, 50, buttonSize, archerTexture);
    Button mageButton(buttonStartX, 150, buttonSize, mageTexture);
    Button artilleryButton(buttonStartX, 250, buttonSize, artilleryTexture);

    // Tipo de torre seleccionada (por defecto, arquero)
    TileType selectedTowerType = TileType::ArcherTower;


        // 👹 Spawn inicial de prueba
    for (int i = 0; i < 5; ++i) {
        Ogre* ogre = new Ogre();
        ogre->setPosition(sf::Vector2f(-i * 100.f, 100.f)); // Espaciados fuera de pantalla
        enemies.push_back(ogre);
    }
    

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

        float deltaTime = clock.restart().asSeconds();

        // Actualizar enemigos
        for (Enemy* enemy : enemies) {
            enemy->update(deltaTime);
        }

        window.clear();
        gameMap.draw(window);

        // 👹 Dibujar enemigos
        for (Enemy* enemy : enemies) {
            enemy->draw(window);
        }

        // 🎨 Dibujar fondo del menú
        sf::RectangleShape menuBackground(sf::Vector2f(menuWidth, rows * tileSize));
        menuBackground.setPosition(cols * tileSize, 0);
        menuBackground.setFillColor(sf::Color(200, 200, 200));
        window.draw(menuBackground);

        // 🎨 Dibujar botones
        archerButton.draw(window);
        mageButton.draw(window);
        artilleryButton.draw(window);

        // 🎨 Dibujar castillo
        sf::Sprite castleSprite;
        castleSprite.setTexture(castleTexture);
        castleSprite.setPosition(castlePosition);
        castleSprite.setScale(tileSize / castleTexture.getSize().x, tileSize / castleTexture.getSize().y);
        window.draw(castleSprite);


        window.display();
    }

    // 🔥 Liberar memoria de los enemigos
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    return 0;
}