#include "Nave.h"

Nave::Nave() {
	
}

Nave::Nave(int x, int y, Texture &texture) {
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(IntRect(13*8+8, 7*8+7, 16, 8));
	this->sprite.setPosition(x, y);
	this->sprite.setScale(3, 3);
	this->velocidad = 5;
	this->vida = 100;
	this->disp = false;
}

void Nave::draw(RenderTarget &rt, RenderStates rs) const {
	rt.draw(this->sprite, rs);
}

void Nave::update() {
	if (Keyboard::isKeyPressed(Keyboard::Right) && ((this->sprite.getPosition().x + this->velocidad) < 552)) {
		this->sprite.move(this->velocidad, 0);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Left) && ((this->sprite.getPosition().x + this->velocidad*-1) > 0)) {
		this->sprite.move(this->velocidad*-1, 0);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Up) && ((this->sprite.getPosition().y + this->velocidad*-1) > 0)) {
		this->sprite.move(0, this->velocidad*-1);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Down) && ((this->sprite.getPosition().y + this->velocidad) < 552)) {
		this->sprite.move(0, this->velocidad);
	}
}

bool Nave::disparo() {
	if (Keyboard::isKeyPressed(Keyboard::Space) && !this->disp) {
		this->disp = true;
		return true;
	} else if (!Keyboard::isKeyPressed(Keyboard::Space)) {
		this->disp = false;
	}
	
	return false;
}

Vector2f Nave::posicion() {
	return this->sprite.getPosition();
}

Sprite& Nave::getSprite() {
	return this->sprite;
}
