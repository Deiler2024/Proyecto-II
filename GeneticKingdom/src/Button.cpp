#include "Button.h" // *Incluye la declaración de la clase Button*
  
// *Constructor de la clase Button, inicializa posición, tamaño y textura del botón*
Button::Button(float x, float y, float size, const sf::Texture& texture) {
    shape.setSize(sf::Vector2f(size, size));                  // *Define el tamaño del botón como un cuadrado*
    shape.setPosition(x, y);                                  // *Ubica el botón en pantalla*
    shape.setFillColor(sf::Color(150, 150, 150));             // *Color de fondo del botón (gris)*

    icon.setTexture(texture);                                 // *Asigna la textura al ícono del botón*
    icon.setPosition(x, y);                                   // *Posiciona el ícono encima del botón*

    float scaleX = size / texture.getSize().x;                // *Escala horizontal para que el ícono quepa en el botón*
    float scaleY = size / texture.getSize().y;                // *Escala vertical*
    icon.setScale(scaleX, scaleY);                            // *Aplica la escala al ícono*
}

// *Dibuja el botón en la ventana*
void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);                                       // *Dibuja el fondo del botón*
    window.draw(icon);                                        // *Dibuja el ícono encima del botón*
}

// *Devuelve true si el mouse hace clic dentro del área del botón*
bool Button::isClicked(float mouseX, float mouseY) const {
    return shape.getGlobalBounds().contains(mouseX, mouseY);  // *Verifica si las coordenadas están dentro del botón*
}
