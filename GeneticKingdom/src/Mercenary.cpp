// Mercenary.cpp
#include "Mercenary.h"                  // Incluye la definición de la clase Mercenary
#include <cmath>                        // Incluye funciones matemáticas como sqrt
#include <iostream>                     // Para imprimir en consola (debug o mensajes de error)
#include "WalkingEnemy.h"              // Herencia desde clase de enemigos que caminan

// Definición e inicialización de variables estáticas compartidas por todos los Mercenary
sf::Texture Mercenary::texture;        // Textura del sprite
bool Mercenary::textureLoaded = false; // Marca si la textura ya ha sido cargada

// Constructor: inicializa atributos del enemigo mercenario
Mercenary::Mercenary(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(90.f, 70.f, 0.1f, 0.9f, 0.1f, spawnCell, castleCell, mapLayout) // vida, velocidad, resistencias
{
    // Si no se ha cargado aún la textura, cargarla desde archivo
    if (!textureLoaded) {
        if (!texture.loadFromFile("./mercenary.png")) { // Cargar la textura
            std::cerr << "Error cargando mercenary.png" << std::endl; // Mensaje de error si falla
            throw std::runtime_error("Error al cargar mercenary.png"); // Lanzar excepción
        } else {
            std::cout << "Mercenary texture loaded correctly!\n"; // Confirmación (debug)
        }
        textureLoaded = true; // Marcar como cargada
    }

    sprite.setTexture(texture);   // Asignar textura al sprite
    sprite.setScale(0.9f, 0.9f);  // Ajustar el tamaño visual del sprite
}

// Actualizar posición del enemigo según su camino
void Mercenary::update(float deltaTime) {
    moveAlongPath(deltaTime); // Movimiento implementado en WalkingEnemy
}

// Dibuja al mercenario en la ventana y su barra de vida
void Mercenary::draw(sf::RenderWindow& window) {
    sprite.setPosition(position); // Coloca el sprite en la posición actual
    window.draw(sprite);          // Dibuja el sprite

    float lifePercent = health / 100.f; // Porcentaje de vida actual (0.0 a 1.0)

    if (lifePercent > 0.f) { // Solo dibujar si está vivo
        sf::RectangleShape lifeBarBg(sf::Vector2f(40.f, 5.f)); // Fondo rojo de la barra de vida
        lifeBarBg.setFillColor(sf::Color::Red);
        lifeBarBg.setPosition(position.x, position.y - 10.f); // Coloca la barra encima del sprite

        sf::RectangleShape lifeBar(sf::Vector2f(40.f * lifePercent, 5.f)); // Barra verde proporcional a la vida
        lifeBar.setFillColor(sf::Color::Green);
        lifeBar.setPosition(position.x, position.y - 10.f);

        window.draw(lifeBarBg); // Dibuja fondo primero
        window.draw(lifeBar);   // Luego la vida restante
    }
}

// Devuelve la recompensa en monedas que otorga el mercenario al morir
int Mercenary::getReward() const {
    return 18; // Monedas ganadas al derrotar al mercenario
}
