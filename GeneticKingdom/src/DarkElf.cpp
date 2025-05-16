// DarkElf.cpp

#include "DarkElf.h"          // *Incluye la declaración de la clase DarkElf*
#include "AStar.h"            // *Para encontrar rutas en el mapa*
#include "WalkingEnemy.h"     // *Base común para enemigos que caminan*

// 🔃 Inicialización de variables estáticas
sf::Texture DarkElf::texture;         // *Textura compartida para todos los elfos oscuros*
bool DarkElf::textureLoaded = false;  // *Bandera para evitar recargar la textura varias veces*

// 🧝‍♂️ Constructor de DarkElf: inicializa estadísticas y camino
DarkElf::DarkElf(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout)
    : WalkingEnemy(80.f, 130.f, 0.8f, 0.1f, 0.8f, spawnCell, castleCell, mapLayout) // *Vida, velocidad, resistencias (flecha, magia, artillería)*
{
    if (!textureLoaded) { // *Carga la textura solo una vez*
        if (!texture.loadFromFile("./darkelf.png")) {
            throw std::runtime_error("Error cargando darkelf.png"); // *Error si no se encuentra la imagen*
        }
        textureLoaded = true;
    }
    sprite.setTexture(texture);        // *Asignar textura al sprite*
    sprite.setScale(0.9f, 0.9f);       // *Escalar imagen (por si es muy grande)*
}

// 🔁 Actualiza posición del enemigo en cada frame
void DarkElf::update(float deltaTime) {
    moveAlongPath(deltaTime); // *Lógica común definida en WalkingEnemy*
}

// 🖼 Dibuja al enemigo y su barra de vida
void DarkElf::draw(sf::RenderWindow& window) {
    sprite.setPosition(position); // *Posiciona sprite gráfico*
    window.draw(sprite);          // *Dibuja al enemigo*

    float lifePercent = health / 100.f; // *Porcentaje de vida (para barra)*
    if (lifePercent > 0.f) {
        sf::RectangleShape lifeBarBg(sf::Vector2f(40.f, 5.f));        // *Fondo rojo de la barra*
        lifeBarBg.setFillColor(sf::Color::Red);
        lifeBarBg.setPosition(position.x, position.y - 10.f);

        sf::RectangleShape lifeBar(sf::Vector2f(40.f * lifePercent, 5.f)); // *Parte verde que indica vida restante*
        lifeBar.setFillColor(sf::Color::Green);
        lifeBar.setPosition(position.x, position.y - 10.f);

        window.draw(lifeBarBg);  // *Dibuja fondo*
        window.draw(lifeBar);    // *Dibuja barra de vida*
    }
}

// 💰 Devuelve cuántas monedas otorga este enemigo al morir
int DarkElf::getReward() const {
    return 15; // *Valor de recompensa fijo*
}

