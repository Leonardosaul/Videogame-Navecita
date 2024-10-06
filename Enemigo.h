#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/**
 * @class Enemigo
 *
 * La clase Enemigo maneja la logica de los enemigos, asi como lo son su posición,
 * su dibujo, su actualización en pantalla y su cambio de dirección.
 *
 * @note Clase Enemigo hereda de la clase sf::Drawable para aprovechar en renderizado
*/
class Enemigo : public Drawable{
	private:
		Sprite sprite;
		int velocidad;
		int estado;
		int tiempo;
		Vector2f posicionInicial;
	public:
		/**
		 * Constructor de la clase, inicializa diversos atributos de la clase
		 *
		 * @param x Posicion del enemigo en el eje x
		 * @param y Posicion del enemigo en el eje y
		 * @param texture Referencia de las texturas que se usaran
		 * @param posicionInicial Inicializa la posicion de los enemigos
		 * @return void
		*/
		Enemigo(int x,int y, Texture &texture, Vector2f posicionInicial);
		
		/**
		 * Metodo para actualizar al enemigo en la ventana
		 *
		 * @return void
		*/
		void Update();
		
		/**
		 * Metodo para cambiar la posicion en horizontal y bajar una posicion en el vertical
		 *
		 * @return void
		*/
		void ChangeDir();
		
		/**
		 * Metodo para obtener la posicion del sprite del enemigo
		 *
		 * @return Vector2f
		*/
		Vector2f Pos();
		
		/**
		 * Metodo encargado de dibujar o renderizar el sprite
		 *
		 * @param rt Destinos donde se puede renderizar
		 * @param rs Contiene informacion sobre el estado de renderizado
		 * @return void
		*/
		virtual void draw(RenderTarget &rt,RenderStates rs) const;
		
};
