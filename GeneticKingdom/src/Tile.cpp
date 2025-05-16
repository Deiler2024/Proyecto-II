#include "Tile.h" // 🔗 Incluye la definición de la clase Tile
#include <SFML/Graphics.hpp> // 🎮 Biblioteca para gráficos

// 🖼️ Texturas globales compartidas para las torres (se cargan una vez)
sf::Texture archerTexture;      // 🏹 Textura de la torre de arqueros
sf::Texture mageTexture;        // 🔮 Textura de la torre de magos
sf::Texture artilleryTexture;   // 💣 Textura de la torre de artillería
bool texturesLoaded = false;    // 📦 Marca si las texturas ya fueron cargadas

// 🧱 Constructor de un tile individual
Tile::Tile(float x, float y, float size)
    : type(TileType::Empty) { // 🔰 Tipo por defecto: vacío
    shape.setSize(sf::Vector2f(size - 1, size - 1)); // 🔲 Resta 1 para dejar espacio entre celdas (bordes visibles)
    shape.setPosition(x, y); // 📍 Posición del tile en la ventana
    shape.setFillColor(sf::Color::White); // 🎨 Color inicial
}

// 🔁 Cambia el tipo del tile y actualiza su color
void Tile::setType(TileType newType) {
    type = newType; // 🔁 Asignar nuevo tipo

    switch (type) {
        case TileType::Empty:
            shape.setFillColor(sf::Color::White); // Blanco para vacíos
            break;
        case TileType::Bridge:
            shape.setFillColor(sf::Color(150, 75, 0)); // Marrón para puentes
            break;
        case TileType::ArcherTower:
        case TileType::MageTower:
        case TileType::ArtilleryTower:
            // No cambiar color, porque se dibuja un sprite encima
            break;
    }
}

// 🔎 Devuelve el tipo actual del tile
TileType Tile::getType() const {
    return type;
}

// 🖼️ Dibuja el tile (con torre o sin ella)
void Tile::draw(sf::RenderWindow& window) const {
    if (!texturesLoaded) { // ✅ Solo cargar una vez
        archerTexture.loadFromFile("./torre_archer.png");     // Cargar textura arquero
        mageTexture.loadFromFile("./torre_mage.png");         // Cargar textura mago
        artilleryTexture.loadFromFile("./torre_artillery.png"); // Cargar textura artillería
        texturesLoaded = true; // ✅ Marcamos como cargadas
    }

    // 🏰 Si hay una torre, dibujar su sprite
    if (type == TileType::ArcherTower || type == TileType::MageTower || type == TileType::ArtilleryTower) {
        sf::Sprite sprite;

        // Seleccionar la textura correspondiente
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

        sprite.setPosition(shape.getPosition()); // 📍 Alinear sprite con el tile
        sprite.setScale(
            (shape.getSize().x + 1) / sprite.getTexture()->getSize().x, // 🔄 Escalar a tamaño tile
            (shape.getSize().y + 1) / sprite.getTexture()->getSize().y
        );

        window.draw(sprite); // 🖼️ Dibuja sprite de torre
    } else {
        window.draw(shape); // 🟫 Si no hay torre, solo dibuja el fondo del tile
    }
}
