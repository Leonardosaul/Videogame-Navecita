#include "Enemigo.h"

Enemigo::Enemigo() {
	
}

Enemigo::Enemigo(int x, int y, Texture &texture, Vector2f p) : velocidad(2), estado(0) {
    point = p;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(point.x, point.y, 8, 8));
    sprite.setPosition(x, y);
    sprite.setScale(3, 3);
}

// Actualiza la lógica del enemigo
void Enemigo::Update(float deltaTime) {
    sprite.move(velocidad, 0); // Mueve el enemigo
}

void Enemigo::ChangeDir() {
	velocidad *= (-1);
    sprite.move(0, 10); // Baja al cambiar de dirección 
}

// Cambia la dirección del enemigo y dispara
void Enemigo::ChangeDir(std::vector<Bala> &balasEnemigos, Texture &texture) {
    velocidad *= (-1);
    sprite.move(0, 10); // Baja al cambiar de dirección

    // Dispara una bala al cambiar de dirección
    balasEnemigos.push_back(Bala(sprite.getPosition().x + 16, sprite.getPosition().y + 24, texture, IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), 5));
}

// Devuelve la posición del enemigo
Vector2f Enemigo::Pos() const {
    return sprite.getPosition();
}

// Dibuja el enemigo
void Enemigo::draw(RenderTarget &rt, RenderStates rs) const {
    rt.draw(sprite, rs);
}

// Devuelve el sprite
const Sprite& Enemigo::getSprite() const {
    return this->sprite;
}

// Mueve el enemigo
void Enemigo::move(float offsetX, float offsetY) {
    this->sprite.move(offsetX, offsetY);
}

// Verifica si el enemigo está en la última fila
bool Enemigo::isInLastRow(size_t totalEnemies, size_t rowCount) const {
    float windowHeight = 800; // Altura de la ventana del juego, ajústalo según tu configuración
    float enemyHeight = this->getSprite().getGlobalBounds().height; // Altura del enemigo
    return (Pos().y + enemyHeight >= windowHeight - enemyHeight); // Ajusta esta lógica según tu diseño
}
