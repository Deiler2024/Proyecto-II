#include "AStar.h" // *Incluye la declaración del algoritmo A* y funciones auxiliares*
#include <queue> // *Para usar priority_queue*
#include <unordered_map> // *Para mapear nodos visitados y costes*
#include <cmath> // *Para abs y cálculos matemáticos*

float heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y); // *Calcula distancia Manhattan entre dos puntos*
}

std::vector<sf::Vector2i> reconstructPath(
    std::unordered_map<sf::Vector2i, sf::Vector2i, std::hash<int>>, // *Prototipo (no usado aquí)*
    sf::Vector2i current
);

struct Node {
    sf::Vector2i pos; // *Posición del nodo en la grilla*
    float fScore; // *Costo estimado total desde inicio hasta destino pasando por este nodo*

    bool operator>(const Node& other) const {
        return fScore > other.fScore; // *Comparación para ordenar en min-heap por fScore*
    }
};

std::vector<sf::Vector2i> findPath(
    const sf::Vector2i& start, // *Punto inicial*
    const sf::Vector2i& goal, // *Punto objetivo*
    const std::vector<std::vector<int>>& mapLayout // *Matriz del mapa*
) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet; // *Nodos por explorar ordenados por menor fScore*
    std::unordered_map<int, sf::Vector2i> cameFrom; // *Mapea nodo actual con su predecesor*
    std::unordered_map<int, float> gScore; // *Costo desde el inicio hasta el nodo actual*

    auto index = [&](const sf::Vector2i& v) { return v.y * mapLayout[0].size() + v.x; }; // *Convierte coordenadas 2D a un índice único 1D*

    openSet.push({start, heuristic(start, goal)}); // *Inicializa openSet con el nodo de inicio*
    gScore[index(start)] = 0.f; // *Costo desde inicio a inicio es 0*

    std::vector<sf::Vector2i> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1} // *Vecinos en 4 direcciones (derecha, izquierda, abajo, arriba)*
    };

    while (!openSet.empty()) {
        sf::Vector2i current = openSet.top().pos; // *Toma el nodo con menor fScore*
        openSet.pop(); // *Lo remueve del conjunto abierto*

        if (current == goal) { // *Si se llegó al destino*
            std::vector<sf::Vector2i> path;
            while (cameFrom.find(index(current)) != cameFrom.end()) {
                path.push_back(current); // *Construye el camino hacia atrás*
                current = cameFrom[index(current)];
            }
            path.push_back(start); // *Incluye el nodo de inicio*
            std::reverse(path.begin(), path.end()); // *Invierte el camino para obtener el orden correcto*
            return path; // *Retorna el camino encontrado*
        }

        for (auto& dir : directions) {
            sf::Vector2i neighbor = current + dir; // *Calcula posición del vecino*
            if (neighbor.x < 0 || neighbor.y < 0 || // *Fuera del mapa*
                neighbor.x >= mapLayout[0].size() ||
                neighbor.y >= mapLayout.size()) {
                continue;
            }

            int cell = mapLayout[neighbor.y][neighbor.x];
            if (cell != 1 && cell != 2) continue; // *Solo caminar por puentes (1) o castillo (2)*

            float tentativeGScore = gScore[index(current)] + 1.f; // *Costo tentativo al vecino*
            if (!gScore.count(index(neighbor)) || tentativeGScore < gScore[index(neighbor)]) {
                cameFrom[index(neighbor)] = current; // *Se guarda el nodo actual como predecesor*
                gScore[index(neighbor)] = tentativeGScore; // *Se actualiza el gScore*
                openSet.push({neighbor, tentativeGScore + heuristic(neighbor, goal)}); // *Se añade el vecino al openSet con su nuevo fScore*
            }
        }
    }

    return {}; // *Retorna camino vacío si no hay ruta posible*
}
