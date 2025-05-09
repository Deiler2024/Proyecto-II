#include "Ogre.h"
#include <cmath>


// 🛠 Definición de las variables estáticas
sf::Texture Ogre::texture;
bool Ogre::textureLoaded = false;

Ogre::Ogre(const sf::Vector2i& startCell, const sf::Vector2i& goalCell, const std::vector<std::vector<int>>& mapLayout)
    : Enemy(150.f, 50.f, 0.5f, 0.2f, 0.3f) // Vida, velocidad, resistencias
{
    if (!textureLoaded) {
        if (!texture.loadFromFile("./ogre.png")) {
            // Puedes mostrar un error si quieres
        }
        textureLoaded = true;
    }

    sprite.setTexture(texture);
    sprite.setScale(0.9f, 0.9f); // Ajusta tamaño si quieres

    path = findPath(startCell, goalCell, mapLayout);
    currentPathIndex = 0;

    if (!path.empty()) {
        position = sf::Vector2f(path[0].x * 50.f, path[0].y * 50.f); // 50 = tamaño de tile
    }
}

void Ogre::update(float deltaTime) {
    if (path.empty() || currentPathIndex >= path.size())
        return;

    sf::Vector2f target(path[currentPathIndex].x * 50.f, path[currentPathIndex].y * 50.f);
    sf::Vector2f direction = target - position;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 2.f) { // ⚡ MÁS PRECISO: cambiar de casilla solo al acercarse mucho
        position = target; // 👈 Ajustamos exacto al centro
        currentPathIndex++;
    } else {
        sf::Vector2f movement = (direction / distance) * moveSpeed * deltaTime;
        position += movement;
    }
}


void Ogre::draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
}
