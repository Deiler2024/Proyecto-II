#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

std::vector<sf::Vector2i> findPath(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& mapLayout
);
