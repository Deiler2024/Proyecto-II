#include "Button.h"


Button::Button(float x, float y, float size, const sf::Texture& texture) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(150, 150, 150)); // Fondo gris

    icon.setTexture(texture);
    icon.setPosition(x, y);

    float scaleX = size / texture.getSize().x;
    float scaleY = size / texture.getSize().y;
    icon.setScale(scaleX, scaleY);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(icon);
}

bool Button::isClicked(float mouseX, float mouseY) const {
    return shape.getGlobalBounds().contains(mouseX, mouseY);
}
