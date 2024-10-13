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

// M�todo para obtener la posici�n exacta de la bala
Vector2f Bala::getPos() const {
    return this->sprite.getPosition();
}

// M�todo para obtener los l�mites globales del sprite (usado en colisiones)
FloatRect Bala::getGlobalBounds() {
    return this->sprite.getGlobalBounds();
}
