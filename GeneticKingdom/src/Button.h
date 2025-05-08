#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Sprite icon;

public:
    Button(float x, float y, float size, const sf::Texture& texture);

    void draw(sf::RenderWindow& window) const;
    bool isClicked(float mouseX, float mouseY) const;
};
