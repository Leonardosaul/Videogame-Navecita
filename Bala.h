#ifndef BALA_H
#define BALA_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Bala : public Drawable {
    private:
        Sprite sprite;
        int velocidad;
    public:
        Bala(int x, int y, Texture &texture, IntRect intRect, int velocidad);
        virtual void draw(RenderTarget &rt, RenderStates rs) const;
        void update();
        FloatRect getGlobalBounds();  // Para colisiones
        Vector2f getPos() const;            // Para obtener la posición
};

#endif
