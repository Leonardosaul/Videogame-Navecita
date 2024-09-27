#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Nave : public Drawable {
	private:
		Sprite sprite;
		int vida;
		int velocidad;
		bool disp;
	public:
		Nave(int x, int y, Texture &texture);
		virtual void draw(RenderTarget &rt, RenderStates rs) const;
		void update();
		bool disparo();
		Vector2f posicion();
};
