#ifndef NIVEL_H
#define NIVEL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Nave.h"
#include "Enemigo.h"

using namespace std;
using namespace sf;

class Nivel {
	private:
		//atributos
		Texture& texture;
		RenderWindow& window;
		Font font;
		Nave nave;
		vector<Enemigo> enemigos;
		int currentLevel;
		Clock clock;
		
		//metodos
		void buildCharacters();
		bool firstLevel();
		bool secondLevel();
		bool thirdLevel();
	public:
		Nivel(Texture &texture, RenderWindow &window, Font font);
		void initiator();
};

#endif
