#include "Ogre.h"                  // Incluye la declaración de la clase Ogre
#include <cmath>                  // Para funciones matemáticas (sqrt)
#include "WalkingEnemy.h"         // Clase base para enemigos que caminan

// 🔄 Definición de las variables estáticas
sf::Texture Ogre::texture;        // Textura compartida entre todos los ogros
bool Ogre::textureLoaded = false; // Bandera para evitar cargar la textura múltiples veces

// 🏗️ Constructor del Ogro
Ogre::Ogre(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(150.f, 50.f, 0.1f, 0.6f, 0.8f, spawnCell, castleCell, mapLayout) // Inicializa atributos del enemigo base
{
    // Carga la textura solo una vez
    if (!textureLoaded) {
        if (!texture.loadFromFile("./ogre.png")) {
            throw std::runtime_error("Error cargando ogre.png"); // Lanza excepción si falla
        }
        textureLoaded = true; // Marca como cargada
    }

    sprite.setTexture(texture);   // Asigna la textura al sprite
    sprite.setScale(0.9f, 0.9f);  // Escala el sprite para ajustarlo al tamaño de los tiles
}

// 🔁 Actualiza la lógica del enemigo (movimiento)
void Ogre::update(float deltaTime) {
    moveAlongPath(deltaTime);     // Se mueve usando el algoritmo A*
}

// 🎨 Dibuja el sprite del enemigo y su barra de vida
void Ogre::draw(sf::RenderWindow& window) {
    sprite.setPosition(position); // Coloca el sprite en la posición actual
    window.draw(sprite);          // Dibuja el sprite en pantalla

    float lifePercent = health / 100.f; // Calcula porcentaje de vida

    if (lifePercent > 0.f) { // Si está vivo, dibuja la barra de vida
        sf::RectangleShape lifeBarBg(sf::Vector2f(40.f, 5.f)); // Fondo rojo
        lifeBarBg.setFillColor(sf::Color::Red);
        lifeBarBg.setPosition(position.x, position.y - 10.f); // Encima del enemigo

        sf::RectangleShape lifeBar(sf::Vector2f(40.f * lifePercent, 5.f)); // Barra verde proporcional
        lifeBar.setFillColor(sf::Color::Green);
        lifeBar.setPosition(position.x, position.y - 10.f);

        window.draw(lifeBarBg);   // Dibuja fondo
        window.draw(lifeBar);     // Dibuja barra encima
    }
}

// 💰 Devuelve la recompensa que da el ogro al ser derrotado
int Ogre::getReward() const {
    return 10; // 10 monedas
}


