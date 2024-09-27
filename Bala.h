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
};
