#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {

    Texture spritesheet;

    if (!spritesheet.loadFromFile("Resources/Sprite/spritesheet.png")) {
        cout << "Error al cargar la textura";
    }

    RenderWindow window(VideoMode(600, 600), "Navecita");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.display();
    }

    return 0;
}

