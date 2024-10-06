#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

/**
 * @class Bala
 *
 * La clase Bala maneja la logica de las balas, asi como lo son su posición,
 * su dibujo, su actualización en pantalla y su cambio de dirección.
 *
 * @note Clase Bala hereda de la clase sf::Drawable para aprovechar en renderizado
*/
class Bala : public Drawable {
    private:
        Sprite sprite;
        int velocidad;
    public:
    	/**
		 * Constructor de la clase, inicializa diversos atributos de la clase
		 *
		 * @param x Posicion del enemigo en el eje x
		 * @param y Posicion del enemigo en el eje y
		 * @param texture Referencia de las texturas que se usaran
		 * @param intRect Inicializa un rectangulo con coordenadas de una textura
		 * @param velocidad Velocidad de las balas
		 * @return void
		*/
        Bala(int x, int y, Texture &texture, IntRect intRect, int velocidad);
        
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
		 * Metodo donde obtendremos los limites globales del objecto en pantalla
		 *
		 * @return FloatRect
		*/
        FloatRect getGlobalBounds();
        
        /**
		 * Metodo para obtener la posicion del sprite del enemigo
		 *
		 * @return Vector2f
		*/
        Vector2f getPos();         
};
