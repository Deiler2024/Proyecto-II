// Harpy.cpp

#include "Harpy.h"                         // *Incluye la definición de la clase Harpy*
#include "WalkingEnemy.h"                  // *Incluye funcionalidades comunes de enemigos que caminan*

// 📦 Inicialización de las variables estáticas de textura
sf::Texture Harpy::texture;               // *Textura compartida entre todas las instancias de Harpy*
bool Harpy::textureLoaded = false;        // *Marca si la textura ya fue cargada para evitar repetirlo*

// 🛠 Constructor de Harpy: define atributos y carga textura si es necesario
Harpy::Harpy(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(60.f, 100.f, 0.5f, 0.5f, 0.0f, spawnCell, castleCell, mapLayout) // Vida, velocidad, resistencias
{
    if (!textureLoaded) { // *Evita recargar la textura si ya se hizo una vez*
        if (!texture.loadFromFile("./harpy.png")) { // *Carga la imagen desde archivo*
            throw std::runtime_error("Error cargando harpy.png"); // *Error si no se encuentra*
        }
        textureLoaded = true; // *Marca que la textura ya está lista*
    }
    sprite.setTexture(texture);           // *Asocia la textura al sprite del enemigo*
    sprite.setScale(0.9f, 0.9f);          // *Escala el sprite para ajustarlo al tamaño del tile*
}

// 🔁 Lógica de movimiento del enemigo (definida en la clase base WalkingEnemy)
void Harpy::update(float deltaTime) {
    moveAlongPath(deltaTime);             // *Movimiento según el camino calculado*
}

// 🎨 Dibuja el sprite y la barra de vida del enemigo
void Harpy::draw(sf::RenderWindow& window) {
    sprite.setPosition(position);         // *Coloca el sprite en la posición actual*
    window.draw(sprite);                  // *Dibuja el sprite en la ventana*

    float lifePercent = health / 100.f;   // *Calcula el porcentaje de vida restante*

    if (lifePercent > 0.f) {              // *Solo dibuja la barra si está vivo*
        sf::RectangleShape lifeBarBg(sf::Vector2f(40.f, 5.f)); // *Fondo rojo de la barra de vida*
        lifeBarBg.setFillColor(sf::Color::Red);
        lifeBarBg.setPosition(position.x, position.y - 10.f); // *Posiciona arriba del sprite*

        sf::RectangleShape lifeBar(sf::Vector2f(40.f * lifePercent, 5.f)); // *Barra verde proporcional a la vida*
        lifeBar.setFillColor(sf::Color::Green);
        lifeBar.setPosition(position.x, position.y - 10.f);

        window.draw(lifeBarBg);           // *Dibuja fondo primero*
        window.draw(lifeBar);             // *Dibuja vida encima*
    }
}

// 💰 Recompensa en monedas al derrotar una Harpy
int Harpy::getReward() const {
    return 12;                            // *Devuelve 12 monedas cuando se derrota a este enemigo*
}
