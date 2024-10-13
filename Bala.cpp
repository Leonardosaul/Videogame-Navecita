#include "Bala.h"

Bala::Bala(int x, int y, Texture &texture, IntRect intRect, int velocidad) {
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(intRect);
    this->sprite.setPosition(x, y);
    this->sprite.setScale(3, 3);
    this->velocidad = velocidad;
}

void Bala::update() {
    this->sprite.move(0, this->velocidad);
}

void Bala::draw(RenderTarget &rt, RenderStates rs) const {
    rt.draw(this->sprite, rs);
}

// Método para obtener la posición exacta de la bala
Vector2f Bala::getPos() const {
    return this->sprite.getPosition();
}

// Método para obtener los límites globales del sprite (usado en colisiones)
FloatRect Bala::getGlobalBounds() {
    return this->sprite.getGlobalBounds();
}
