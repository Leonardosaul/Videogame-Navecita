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
		bool shot;
	public:
		Enemigo(); // Constructor por defecto
	    Enemigo(int x, int y, Texture &texture, Vector2f p); // Constructor con par�metros
	    void Update(float deltaTime); // Actualiza la l�gica del enemigo
	    void ChangeDirAll(std::vector<Bala> &balasEnemigos, Texture &texture); // Cambia la direcci�n y dispara
	    void ChangeDir();
	    void ChangeDirIfLastRow(std::vector<Enemigo>& enemigos, std::vector<Bala>& balasEnemigos, Texture& texture);
	    Vector2f Pos() const; // Devuelve la posici�n del enemigo
	    virtual void draw(RenderTarget &rt, RenderStates rs) const; // Dibuja el enemigo
	    const Sprite& getSprite() const; // Devuelve el sprite
	    void move(float offsetX, float offsetY); // Mueve el enemigo
	    bool isInLastRow(size_t totalRows) const; // Verifica si est� en la �ltima fila
	    bool hasShot() const;
	    void setShot(bool value);
};

#endif
