#include "WaveManager.h"                   // *Incluye la definición de la clase WaveManager*
#include <random>                         // *Para generación de números aleatorios*

// Variables externas que controlan la generación, fitness, mutaciones globales
extern int currentGeneration;              // *Número de generación actual*
extern std::vector<float> fitnessValues;   // *Vector con valores de fitness de la generación*
extern float mutationProbability;           // *Probabilidad de que ocurra una mutación*
extern int totalMutations;                   // *Contador total de mutaciones*

// Constructor que inicializa puntos de spawn, destino y el layout del mapa
WaveManager::WaveManager(const sf::Vector2i& spawn, const sf::Vector2i& goal, const std::vector<std::vector<int>>& layout)
    : spawnPoint(spawn), goalPoint(goal), mapLayout(layout) {
    generateNextWave();                    // *Genera la primera oleada al iniciar*
}

// Actualiza el estado de la oleada y los enemigos en juego
void WaveManager::update(float deltaTime, std::vector<Enemy*>& enemies) {
    spawnTimer += deltaTime;               // *Incrementa el temporizador de spawn*

    // Si ya pasó el intervalo y hay enemigos pendientes, spawn el siguiente
    if (spawnTimer >= spawnInterval && !pendingEnemies.empty()) {
        Enemy* next = pendingEnemies.front(); // *Obtiene el siguiente enemigo pendiente*
        pendingEnemies.pop();                  // *Lo remueve de la cola de pendientes*
        enemies.push_back(next);               // *Lo agrega a la lista de enemigos activos*
        spawnTimer = 0.f;                      // *Reinicia el temporizador de spawn*
    }

    // Si no quedan enemigos pendientes ni vivos, genera la siguiente oleada
    if (pendingEnemies.empty() && enemies.empty()) {
        generateNextWave();
    }
}

// Devuelve si hay enemigos pendientes para spawnear
bool WaveManager::hasPendingEnemies() const {
    return !pendingEnemies.empty();
}

// Genera la próxima oleada con enemigos nuevos, con mutaciones y fitness calculados
void WaveManager::generateNextWave() {
    waveNumber++;                           // *Incrementa el contador de oleadas*

    int totalEnemies = 4 + waveNumber;     // *Aumenta la cantidad de enemigos en cada oleada*

    // Resetea contadores y registros para la nueva generación
    currentGeneration++;                   // *Incrementa generación global*
    enemiesKilledThisWave = 0;             // *Reinicia conteo de enemigos muertos en oleada*
    fitnessValues.clear();                 // *Limpia los valores de fitness previos*

    // Inicializa generadores aleatorios para tipos de enemigos y mutaciones
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> enemyType(0, 3);          // *Tipos de enemigos entre 0 y 3*
    std::uniform_real_distribution<float> mutationChance(0.f, 1.f); // *Probabilidad de mutar*
    std::uniform_real_distribution<float> mutationDelta(-0.1f, 0.1f); // *Magnitud de la mutación*

    for (int i = 0; i < totalEnemies; ++i) {
        float health = 100.f;               // *Valor base de vida*
        float speed = 60.f;                 // *Velocidad base*
        float arrowRes = 0.3f;              // *Resistencia base a flechas*
        float magicRes = 0.3f;              // *Resistencia base a magia*
        float artilleryRes = 0.3f;          // *Resistencia base a artillería*

        // Aplicar mutación si la probabilidad lo permite
        if (mutationChance(gen) < mutationProbability) {
            speed += mutationDelta(gen) * speed;                  // *Modifica velocidad*
            health += mutationDelta(gen) * health;                // *Modifica vida*
            arrowRes = std::clamp(arrowRes + mutationDelta(gen), 0.f, 1.f);       // *Clamp entre 0 y 1*
            magicRes = std::clamp(magicRes + mutationDelta(gen), 0.f, 1.f);
            artilleryRes = std::clamp(artilleryRes + mutationDelta(gen), 0.f, 1.f);
            totalMutations++;                                      // *Incrementa contador global de mutaciones*
        }

        float fitness = speed * 0.5f + health * 0.5f;               // *Calcula fitness básico (ponderado)*
        fitnessValues.push_back(fitness);                           // *Guarda fitness para análisis*

        int type = enemyType(gen);                                  // *Selecciona aleatoriamente tipo de enemigo*
        switch (type) {
            case 0:
                pendingEnemies.push(new Ogre(spawnPoint, goalPoint, mapLayout));      // *Añade Ogre a pendientes*
                break;
            case 1:
                pendingEnemies.push(new DarkElf(spawnPoint, goalPoint, mapLayout));  // *Añade DarkElf a pendientes*
                break;
            case 2:
                pendingEnemies.push(new Harpy(spawnPoint, goalPoint, mapLayout));    // *Añade Harpy a pendientes*
                break;
            case 3:
                pendingEnemies.push(new Mercenary(spawnPoint, goalPoint, mapLayout));// *Añade Mercenary a pendientes*
                break;
        }
    }
}
