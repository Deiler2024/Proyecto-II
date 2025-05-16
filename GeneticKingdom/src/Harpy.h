// Harpy.h
#pragma once                                      // *Previene inclusiones múltiples del archivo*
#include "WalkingEnemy.h"                        // *Incluye la clase base para enemigos que caminan*
#include <SFML/Graphics.hpp>                     // *Incluye funcionalidades gráficas de SFML*

class Harpy : public WalkingEnemy {             // *Clase Harpy que hereda de WalkingEnemy*
private:
    static sf::Texture texture;                  // *Textura estática compartida por todas las Harpías*
    static bool textureLoaded;                    // *Indica si la textura ya fue cargada para evitar recarga*
    sf::Sprite sprite;                           // *Sprite para representar gráficamente al enemigo*

public:
    // Constructor con posición de spawn, objetivo y layout del mapa
    Harpy(const sf::Vector2i& spawnCell, const sf::Vector2i& castleCell, const std::vector<std::vector<int>>& mapLayout);

    void update(float deltaTime) override;      // *Actualiza la lógica/movimiento del enemigo*
    void draw(sf::RenderWindow& window) override;  // *Dibuja el enemigo en la ventana*
    int getReward() const override;              // *Devuelve la recompensa al morir este enemigo*
};
