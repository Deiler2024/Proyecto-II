#include "Tile.h"
#include <SFML/Graphics.hpp>

// 🖼️ Texturas globales para cada tipo de torre
sf::Texture archerTexture;
sf::Texture mageTexture;
sf::Texture artilleryTexture;
bool texturesLoaded = false;

Tile::Tile(float x, float y, float size)
    : type(TileType::Empty) {
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
        case TileType::Bridge:
            shape.setFillColor(sf::Color(150, 75, 0)); // Marrón
            break;
        case TileType::ArcherTower:
        case TileType::MageTower:
        case TileType::ArtilleryTower:
            // No cambiamos color, porque dibujaremos un sprite en draw()
            break;
    }
}

TileType Tile::getType() const {
    return type;
}

void Tile::draw(sf::RenderWindow& window) const {
    if (!texturesLoaded) {
        // Solo cargar las texturas una vez
        archerTexture.loadFromFile("/home/deiler/Documentos/GitHub/Proyecto-II/GeneticKingdom/src/archer.png");
        mageTexture.loadFromFile("/home/deiler/Documentos/GitHub/Proyecto-II/GeneticKingdom/src/mage.png");
        artilleryTexture.loadFromFile("/home/deiler/Documentos/GitHub/Proyecto-II/GeneticKingdom/src/artillery.png");
        texturesLoaded = true;
    }

    if (type == TileType::ArcherTower || type == TileType::MageTower || type == TileType::ArtilleryTower) {
        sf::Sprite sprite;

        switch (type) {
            case TileType::ArcherTower:
                sprite.setTexture(archerTexture);
                break;
            case TileType::MageTower:
                sprite.setTexture(mageTexture);
                break;
            case TileType::ArtilleryTower:
                sprite.setTexture(artilleryTexture);
                break;
            default:
                break;
        }

        sprite.setPosition(shape.getPosition());
        sprite.setScale(
            (shape.getSize().x + 1) / sprite.getTexture()->getSize().x,
            (shape.getSize().y + 1) / sprite.getTexture()->getSize().y
        ); // Ajustamos el sprite para que encaje en el tile
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}
