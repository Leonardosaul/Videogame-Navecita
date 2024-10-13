#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Bala.h"

using namespace std;
using namespace sf;

class Enemigo : public Drawable{
	private:
		Sprite sprite;
		int velocidad;
		int estado;
		int tiempo;
		Vector2f point;
	public:
		Enemigo(); // Constructor por defecto
	    Enemigo(int x, int y, Texture &texture, Vector2f p); // Constructor con parámetros
	    void Update(float deltaTime); // Actualiza la lógica del enemigo
	    void ChangeDir(std::vector<Bala> &balasEnemigos, Texture &texture); // Cambia la dirección y dispara
	    void ChangeDir();
	    Vector2f Pos() const; // Devuelve la posición del enemigo
	    virtual void draw(RenderTarget &rt, RenderStates rs) const; // Dibuja el enemigo
	    const Sprite& getSprite() const; // Devuelve el sprite
	    void move(float offsetX, float offsetY); // Mueve el enemigo
	    bool isInLastRow(size_t totalEnemies, size_t rowCount) const; // Verifica si está en la última fila
};

#endif
