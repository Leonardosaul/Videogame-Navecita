#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Nave.h"
#include "Bala.h"

using namespace std;
using namespace sf;

int main() {
	
	Texture spritesheet;
	
	if (!spritesheet.loadFromFile("Resources/Sprite/spritesheet.png")) {
		cout<<"Error al cargar la textura";
	}
	
	Nave nave(288, 555, spritesheet);
	
	vector<Bala> balasNave;
	
	RenderWindow window(VideoMode(600, 600), "Navecita");
	window.setFramerateLimit(60);
	
	while (window.isOpen()) {
		Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		
		nave.update();
		
		if (nave.disparo()) {
			Bala bala(nave.posicion().x + 24, nave.posicion().y - 24, spritesheet, IntRect(13*8+16, 6*8+6, 8, 8), -5);
			balasNave.push_back(bala);
		}
		
		for (int i = 0; i < (int)balasNave.size(); i++) {
			balasNave[i].update();
		}
		
		window.clear();
		window.draw(nave);
		
		for (int i = 0; i < (int)balasNave.size(); i++) {
			window.draw(balasNave[i]);
		}
		
		window.display();
	}
	
    return 0;
}
