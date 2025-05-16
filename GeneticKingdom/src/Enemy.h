#pragma once                                // *Evita que este archivo se incluya más de una vez*

#include <SFML/Graphics.hpp>               // *Incluye SFML para manejar gráficos (posiciones, dibujo, etc.)*

// 🎯 Clase base abstracta para todos los enemigos del juego
class Enemy {
protected:
    float health;                          // *Vida actual del enemigo*
    float speed;                           // *Velocidad de movimiento*
    float arrowResistance;                 // *Resistencia a flechas (entre 0 y 1)*
    float magicResistance;                 // *Resistencia a magia*
    float artilleryResistance;             // *Resistencia a artillería*
    sf::Vector2f position;                 // *Posición actual del enemigo en el mapa*

public:
    // 🔧 Constructor: inicializa todas las estadísticas del enemigo
    Enemy(float health, float speed, float arrowRes, float magicRes, float artilleryRes);

    // 🔁 Función virtual pura que obliga a las subclases a implementar cómo se actualiza (movimiento)
    virtual void update(float deltaTime) = 0;

    // 🎨 Función virtual pura que obliga a las subclases a implementar cómo se dibuja
    virtual void draw(sf::RenderWindow& window) = 0;

    // 📏 Devuelve la salud actual
    float getHealth() const;

    // 📍 Devuelve la posición actual
    sf::Vector2f getPosition() const;

    // 🧭 Permite modificar directamente la posición
    void setPosition(const sf::Vector2f& pos) {
        position = pos;
    }

    // 💥 Aplica daño al enemigo teniendo en cuenta su resistencia al tipo de ataque
    void takeDamage(float amount, const std::string& damageType);

    // 🧹 Destructor virtual por si hay recursos dinámicos en subclases
    virtual ~Enemy() = default;

    // 🧬 Permite modificar dinámicamente las estadísticas del enemigo (usado en mutaciones)
    void setStats(float newHealth, float newSpeed, float arrowRes, float magicRes, float artilleryRes) {
        health = newHealth;
        speed = newSpeed;
        arrowResistance = arrowRes;
        magicResistance = magicRes;
        artilleryResistance = artilleryRes;
    }

    // 💰 Define la recompensa en monedas al derrotar al enemigo (cada tipo define su valor)
    virtual int getReward() const = 0;
};


