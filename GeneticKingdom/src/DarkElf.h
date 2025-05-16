// DarkElf.h

#pragma once  // *Evita múltiples inclusiones del mismo archivo durante la compilación*

#include "Enemy.h"            // *Clase base Enemy*
#include <SFML/Graphics.hpp>  // *Para usar sf::Sprite y sf::Texture*
#include "AStar.h"            // *Para funciones relacionadas al pathfinding (camino)*
#include "WalkingEnemy.h"     // *Clase base para enemigos que caminan con lógica común*

// 🧝‍♂️ Clase que representa a un Elfo Oscuro enemigo
class DarkElf : public WalkingEnemy { // *Hereda movimiento y atributos básicos*
private:
    static sf::Texture texture;       // *Textura compartida para todos los DarkElfs*
    static bool textureLoaded;        // *Bandera para evitar cargar la textura varias veces*
    sf::Sprite sprite;                // *Imagen que se muestra en pantalla*

public:
    // 🏁 Constructor: define posición inicial y genera su camino al castillo
    DarkElf(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout);

    // 🔁 Lógica de actualización de movimiento por frame
    void update(float deltaTime) override;

    // 🖼 Dibuja el sprite y la barra de vida en pantalla
    void draw(sf::RenderWindow& window) override;

    // 💰 Devuelve la cantidad de monedas que otorga al morir
    int getReward() const override;
};
