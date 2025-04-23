#include "Map.h"

#include "Map.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Genetic Kingdom");
    window.setFramerateLimit(60);

    const int rows = 12;
    const int cols = 16;
    const float tileSize = 50.0f;

    Map gameMap(rows, cols, tileSize);

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
