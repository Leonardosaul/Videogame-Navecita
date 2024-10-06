#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

/**
 * @class Nave
 *
 * La clase Nave maneja la logica de la nave, asi como lo son su posición,
 * su dibujo, su actualización en pantalla y su cambio de dirección.
 *
 * @note Clase Nave hereda de la clase sf::Drawable para aprovechar en renderizado
*/
class Nave : public Drawable {
	private:
		Sprite sprite;
		int vida;
		int velocidad;
		bool disp;
	public:
		/**
		 * Constructor de la clase, inicializa diversos atributos de la clase
		 *
		 * @param x Posicion del enemigo en el eje x
		 * @param y Posicion del enemigo en el eje y
		 * @param texture Referencia de las texturas que se usaran
		 * @return void
		*/
		Nave(int x, int y, Texture &texture);
		
		/**
		 * Metodo encargado de dibujar o renderizar el sprite
		 *
		 * @param rt Destinos donde se puede renderizar
		 * @param rs Contiene informacion sobre el estado de renderizado
		 * @return void
		*/
		virtual void draw(RenderTarget &rt, RenderStates rs) const;
		
		/**
		 * Metodo para actualizar la bala en la ventana
		 *
		 * @return void
		*/
		void update();
		
		/**
		 * Metodo para comprobar si la nave dispara
		 *
		 * @return boolean
		*/
		bool disparo();
		
		/**
		 * Metodo para obtener la posicion del sprite del enemigo
		 *
		 * @return Vector2f
		*/
		Vector2f posicion();
};
