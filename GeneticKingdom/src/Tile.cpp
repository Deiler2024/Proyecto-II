#include "Tile.h"
#include <SFML/Graphics.hpp>

// 🖼️ Textura global de torre
sf::Texture towerTexture;
bool towerTextureLoaded = false;

Tile::Tile(float x, float y, float size) : type(TileType::Empty) {
    shape.setSize(sf::Vector2f(size - 1, size - 1)); // -1 para que se vean los bordes
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Tile::setType(TileType newType) {
    type = newType;
    switch (type) {
        case TileType::Empty:
            shape.setFillColor(sf::Color::White);
            break;
        case TileType::Tower:
            // Cuando es torre, no cambiamos color. Dibujaremos sprite en draw()
            break;
        case TileType::Path:
            shape.setFillColor(sf::Color::Yellow);
            break;
        case TileType::Bridge:
            shape.setFillColor(sf::Color(100, 100, 100));
            break;
    }
}

TileType Tile::getType() const {
    return type;
}

void Tile::draw(sf::RenderWindow& window) const {
    if (type == TileType::Tower) {
        if (!towerTextureLoaded) {
            if (!towerTexture.loadFromFile("/home/deiler/Documentos/GitHub/Proyecto-II/GeneticKingdom/src/tower.png")) {
                // Si falla la carga podrías manejar un error aquí
            }
            towerTextureLoaded = true;
        }
        sf::Sprite sprite;
        sprite.setTexture(towerTexture);
        sprite.setPosition(shape.getPosition());
        sprite.setScale(
            (shape.getSize().x + 1) / towerTexture.getSize().x, 
            (shape.getSize().y + 1) / towerTexture.getSize().y
        ); // Ajustamos el sprite para que encaje en el tile
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}
