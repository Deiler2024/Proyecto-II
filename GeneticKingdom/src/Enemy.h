#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
protected:
    float health;
    float speed;
    float arrowResistance;
    float magicResistance;
    float artilleryResistance;
    sf::Vector2f position; // Posición actual del enemigo

public:
    Enemy(float health, float speed, float arrowRes, float magicRes, float artilleryRes);

    virtual void update(float deltaTime) = 0; // Movimiento
    virtual void draw(sf::RenderWindow& window) = 0;

    float getHealth() const;
    sf::Vector2f getPosition() const;

    // 🆕 Esta función nueva:
    void setPosition(const sf::Vector2f& pos) {
        position = pos;
    }
    
    void takeDamage(float amount, const std::string& damageType); // Daño recibido según tipo

    virtual ~Enemy() = default;

    void setStats(float newHealth, float newSpeed, float arrowRes, float magicRes, float artilleryRes) {
        health = newHealth;
        speed = newSpeed;
        arrowResistance = arrowRes;
        magicResistance = magicRes;
        artilleryResistance = artilleryRes;
    }
    virtual int getReward() const = 0; // ¡Recompensa al morir!


};


