#include <iostream>
#include <SFML/Graphics.hpp>

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
		Enemigo(int x,int y, Texture &texture, Vector2f p);
		void Update();
		void ChangeDir();
		Vector2f Pos();
		virtual void draw(RenderTarget &rt,RenderStates rs) const;
		
};
