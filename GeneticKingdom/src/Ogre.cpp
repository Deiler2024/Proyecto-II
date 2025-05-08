#include "Ogre.h"
#include <iostream>

// Inicializamos las variables estáticas
sf::Texture Ogre::texture;
bool Ogre::textureLoaded = false;

Ogre::Ogre()
    : Enemy(150.f, 50.f, 0.5f, 0.2f, 0.3f) // vida, velocidad, resistencias
{
    if (!textureLoaded) {
        if (!texture.loadFromFile("./ogre.png")) {
            // Manejar error si la imagen no se carga
            std::cerr << "Error al cargar ogre.png" << std::endl;
        }
        textureLoaded = true;



    }

    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f); // Ajustamos tamaño si es necesario
    sprite.setPosition(position);
}

void Ogre::update(float deltaTime) {
    position.x += speed * deltaTime;
    sprite.setPosition(position);
}

void Ogre::draw(sf::RenderWindow& window) {
    sprite.setPosition(position); // <- Asegura que el sprite siga la posición lógica
    window.draw(sprite);
}
