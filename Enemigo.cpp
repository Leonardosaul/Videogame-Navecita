#include "Enemigo.h"

Enemigo::Enemigo() {
	
}

Enemigo::Enemigo(int x, int y, Texture &texture, Vector2f p) : velocidad(2), estado(0) {
    point = p;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(point.x, point.y, 8, 8));
    sprite.setPosition(x, y);
    sprite.setScale(3, 3);
    this->shot = false;
}

// Actualiza la lógica del enemigo
void Enemigo::Update(float deltaTime) {
    sprite.move(velocidad, 0);
}

void Enemigo::ChangeDir() {
	velocidad *= (-1);
    sprite.move(0, 10);
}

// Cambia la dirección del enemigo y dispara
void Enemigo::ChangeDirAll(std::vector<Bala> &balasEnemigos, Texture &texture) {
    velocidad *= (-1);
    sprite.move(0, 10);

    // Dispara una bala al cambiar de dirección
    balasEnemigos.push_back(Bala(sprite.getPosition().x + 16, sprite.getPosition().y + 24, texture, IntRect(13*8+8,8*2+2,8,8), 5));
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

bool Enemigo::isInLastRow(size_t totalRows) const {
    // Obtenemos la altura de la ventana
    float windowHeight = 600;
    // Obtenemos la altura de cada enemigo
    float enemyHeight = this->getSprite().getGlobalBounds().height;
    
    // Comprobamos si la posición y del enemigo está en la última fila
    return (Pos().y + enemyHeight >= windowHeight - enemyHeight * (totalRows - 1));
}

void Enemigo::ChangeDirIfLastRow(std::vector<Enemigo>& enemigos, std::vector<Bala>& balasEnemigos, Texture& texture) {
    // Cambia de dirección
    ChangeDir();

    // Verificar si hay al menos 4 filas y que la fila actual es la última
    size_t totalEnemies = enemigos.size();
    size_t enemiesPerRow = 8;  // Asumiendo que siempre hay 8 enemigos por fila
    size_t lastRowStart = (totalEnemies / enemiesPerRow - 1) * enemiesPerRow;
    size_t lastRowEnd = lastRowStart + enemiesPerRow;

    // Solo disparar si hay enemigos en la última fila
    for (size_t i = lastRowStart; i < lastRowEnd; ++i) {
        if (i < totalEnemies && !enemigos[i].hasShot()) {  // Comprobar si no ha disparado
            balasEnemigos.push_back(Bala(enemigos[i].Pos().x + 16, enemigos[i].Pos().y + 24, texture,
                                          IntRect(13*8+8,8*2+2,8,8), 5));
            enemigos[i].setShot(true);  // Marcar como disparado
        }
    }
}

bool Enemigo::hasShot() const { 
	return shot; 
}

void Enemigo::setShot(bool value) { 
	shot = value; 
} 
