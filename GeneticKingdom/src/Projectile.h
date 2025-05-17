#pragma once // ⚠️ Asegura que el archivo se incluya solo una vez por compilación

#include <SFML/Graphics.hpp> // 🎮 Librería gráfica SFML
#include "Enemy.h"           // 👹 Para apuntar a enemigos
#include <string>            // 📝 Para el tipo de daño como texto

// 💥 Clase que representa un proyectil lanzado por una torre
class Projectile {
private:
    sf::Sprite sprite;         // 🎯 Imagen del proyectil
    sf::Vector2f velocity;     // 🔽 No se usa actualmente, pero reservado para movimiento manual
    float speed;               // 🚀 Velocidad del proyectil
    float damage;              // 💣 Daño que inflige al impactar
    Enemy* target;             // 👹 Enemigo al que persigue
    std::string damageType;    // 🔥 Tipo de daño: "arrow", "magic", "artillery"
    bool active;               // ✅ Si aún sigue en movimiento
    sf::Vector2f fallbackTargetPos; // 🆕 Última posición válida del enemigo
    bool lostTarget = false;        // 🆕 Flag para saber si perdió el objetivo


public:
    // 🛠 Constructor que inicializa todos los atributos
    Projectile(const sf::Vector2f& startPos, Enemy* target, float speed, float damage, const std::string& damageType, sf::Texture& texture);

    void update(float deltaTime);              // 🔄 Actualiza la posición y lógica del proyectil
    void draw(sf::RenderWindow& window) const; // 🎨 Dibuja el proyectil en pantalla
    bool isActive() const;                     // 🔎 Indica si el proyectil sigue vivo (activo)
};
