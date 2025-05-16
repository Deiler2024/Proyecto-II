#pragma once

#include <queue>                     // *Para la cola de enemigos pendientes*
#include <SFML/System/Vector2.hpp>   // *Para usar vectores 2D de SFML*
#include "Enemy.h"                   // *Clase base Enemy*
#include "Ogre.h"                    // *Enemigo Ogre*
#include "DarkElf.h"                 // *Enemigo DarkElf*
#include "Harpy.h"                   // *Enemigo Harpy*
#include "Mercenary.h"               // *Enemigo Mercenary*

class WaveManager {
private:
    int waveNumber = 0;                // *Número de la oleada actual*
    float spawnTimer = 0.f;            // *Temporizador para controlar spawn*
    float spawnInterval = 1.0f;        // *Intervalo de tiempo entre spawns*

    std::queue<Enemy*> pendingEnemies; // *Cola de enemigos que aún no han aparecido*
    sf::Vector2i spawnPoint;           // *Posición donde aparecen los enemigos*
    sf::Vector2i goalPoint;            // *Posición objetivo de los enemigos (castillo)*
    std::vector<std::vector<int>> mapLayout; // *Mapa para el pathfinding*

    // 📊 Estadísticas de la oleada
    int enemiesKilledThisWave = 0;     // *Contador de enemigos muertos en esta oleada*

public:
    // Constructor que recibe puntos de spawn, objetivo y layout
    WaveManager(const sf::Vector2i& spawn, const sf::Vector2i& goal, const std::vector<std::vector<int>>& layout);

    // Actualiza el estado de la oleada (spawns, etc.)
    void update(float deltaTime, std::vector<Enemy*>& enemies);

    // Consulta si hay enemigos pendientes por aparecer
    bool hasPendingEnemies() const;

    // Genera la siguiente oleada de enemigos
    void generateNextWave();

    // 📊 Métodos para obtener estadísticas desde fuera
    int getWaveNumber() const { return waveNumber; }                 // *Devuelve el número de oleada*
    int getEnemiesKilledThisWave() const { return enemiesKilledThisWave; } // *Devuelve muertos en oleada*

    // Incrementa el contador de enemigos muertos (debe llamarse al matar un enemigo)
    void incrementEnemiesKilled() { enemiesKilledThisWave++; }
};
