#include <iostream>
#include <SFML/Graphics.hpp>

#include "Nivel.h"

using namespace std;
using namespace sf;

int main() {

    Texture spritesheet;

    if (!spritesheet.loadFromFile("Resources/Sprite/spritesheet.png")) {
        cout << "Error al cargar la textura";
        return -1;
    }
    
    Font textFont;
    if (!textFont.loadFromFile("Resources/Font/SixtyfourConvergence-Regular.ttf")) {
        std::cerr << "Error cargando la fuente";
        return -1;
    }
    
    RenderWindow window(VideoMode(600, 600), "Navecita");
    window.setFramerateLimit(60);
    
    Nivel nivel(spritesheet, window, textFont);
    
    nivel.initiator();

    return 0;
}

