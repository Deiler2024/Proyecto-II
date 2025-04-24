#include "Tile.h"

Tile::Tile(float x, float y, float size) : type(TileType::Empty) {
    shape.setSize(sf::Vector2f(size - 1, size - 1)); // -1 para que se vean los bordes
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Tile::setType(TileType newType) {
    type = newType;
    switch (type) {
        case TileType::Empty:  shape.setFillColor(sf::Color::White); break;
        case TileType::Tower:  shape.setFillColor(sf::Color::Green); break;
        case TileType::Path:   shape.setFillColor(sf::Color::Yellow); break;
        case TileType::Bridge: shape.setFillColor(sf::Color(100, 100, 100)); break;

 
    }
}

TileType Tile::getType() const {
    return type;
}

void Tile::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}
