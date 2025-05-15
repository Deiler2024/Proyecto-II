#pragma once // ⚠️ Asegura que este encabezado se incluya solo una vez durante la compilación

#include <SFML/Graphics.hpp> // *Incluye la biblioteca gráfica SFML necesaria para botones*

// 🎯 Clase que representa un botón gráfico en pantalla
class Button {
private:
    sf::RectangleShape shape; // *Forma del botón (cuadro base)*
    sf::Sprite icon;          // *Ícono o imagen que se muestra dentro del botón*

public:
    // 📦 Constructor: inicializa posición, tamaño e imagen del botón
    Button(float x, float y, float size, const sf::Texture& texture);

    // 🖼 Dibuja el botón en la ventana
    void draw(sf::RenderWindow& window) const;

    // 🖱 Detecta si se hizo clic en el botón
    bool isClicked(float mouseX, float mouseY) const;
};
