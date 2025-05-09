#include "AStar.h"
#include <queue>
#include <unordered_map>
#include <cmath>

float heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y); // Manhattan distance
}

std::vector<sf::Vector2i> reconstructPath(
    std::unordered_map<sf::Vector2i, sf::Vector2i, std::hash<int>>,
    sf::Vector2i current
);

struct Node {
    sf::Vector2i pos;
    float fScore;

    bool operator>(const Node& other) const {
        return fScore > other.fScore;
    }
};

std::vector<sf::Vector2i> findPath(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& mapLayout
) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::unordered_map<int, sf::Vector2i> cameFrom;
    std::unordered_map<int, float> gScore;

    auto index = [&](const sf::Vector2i& v) { return v.y * mapLayout[0].size() + v.x; };

    openSet.push({start, heuristic(start, goal)});
    gScore[index(start)] = 0.f;

    std::vector<sf::Vector2i> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    while (!openSet.empty()) {
        sf::Vector2i current = openSet.top().pos;
        openSet.pop();

        if (current == goal) {
            std::vector<sf::Vector2i> path;
            while (cameFrom.find(index(current)) != cameFrom.end()) {
                path.push_back(current);
                current = cameFrom[index(current)];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto& dir : directions) {
            sf::Vector2i neighbor = current + dir;
            if (neighbor.x < 0 || neighbor.y < 0 ||
                neighbor.x >= mapLayout[0].size() ||
                neighbor.y >= mapLayout.size()) {
                continue;
            }

            int cell = mapLayout[neighbor.y][neighbor.x];
            if (cell != 1 && cell != 2) continue; // Solo caminar por puente o castillo

            float tentativeGScore = gScore[index(current)] + 1.f;
            if (!gScore.count(index(neighbor)) || tentativeGScore < gScore[index(neighbor)]) {
                cameFrom[index(neighbor)] = current;
                gScore[index(neighbor)] = tentativeGScore;
                openSet.push({neighbor, tentativeGScore + heuristic(neighbor, goal)});
            }
        }
    }

    return {}; // No se encontró camino
}
