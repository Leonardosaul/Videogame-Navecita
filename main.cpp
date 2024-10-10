#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Nave.h"
#include "Bala.h"
#include "Enemigo.h"

using namespace std;
using namespace sf;

int main() {

    Texture spritesheet;

    if (!spritesheet.loadFromFile("Resources/Sprite/spritesheet.png")) {
        cout << "Error al cargar la textura";
    }

    Nave nave(288, 555, spritesheet);

    bool balaActiva = false;
    vector<Bala> balasNave;
    IntRect balaRect;

    vector<vector<Enemigo> > enemigo(7, vector<Enemigo>(12, Enemigo(0, 0, spritesheet, Vector2f(0, 0))));
    IntRect enemigoRect;
    Vector2f sectionSpritesheet;

    int dirEnemigo = 1;
    int maxX, minX;

    for (int i = 0; i < (int)enemigo.size(); i++) {
        for (int j = 0; j < (int)enemigo[i].size(); j++) {
            if (i == 0) {
                sectionSpritesheet = Vector2f(0, 0);
            } else if (i < 3) {
                sectionSpritesheet = Vector2f(0, 9);
            } else if (i < 5) {
                sectionSpritesheet = Vector2f(0, 18);
            } else if (i < 7) {
                sectionSpritesheet = Vector2f(0, 27);
            }
            enemigo[i][j] = Enemigo(j * 30 + 24, i * 30 + 24, spritesheet, sectionSpritesheet);
        }
    }

    RenderWindow window(VideoMode(600, 600), "Navecita");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        nave.update();

        if (nave.disparo()) {
		    Bala bala(nave.posicion().x + 24, nave.posicion().y - 24, spritesheet, IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), -5);
		    balasNave.push_back(bala);
		}

        for (int i = 0; i < (int)balasNave.size(); i++) {
		    balasNave[i].update();
		
		    if (balasNave[i].getPos().y < -24) {
		        balasNave.erase(balasNave.begin() + i);
		        i--; 
		    }
		
		    balaRect = IntRect(balasNave[i].getPos().x, balasNave[i].getPos().y, 3, 8);
		    for (int fila = 0; fila < (int)enemigo.size(); fila++) {
		        for (int col = 0; col < (int)enemigo[fila].size(); col++) {
		            enemigoRect = IntRect(enemigo[fila][col].Pos().x, enemigo[fila][col].Pos().y, 24, 24);
		            if (enemigoRect.intersects(balaRect)) {
		                enemigo[fila].erase(enemigo[fila].begin() + col); 
		                balasNave.erase(balasNave.begin() + i); // Eliminar bala
		                i--;  // Decrementar índice porque eliminamos una bala
		                break;
		            }
		        }
		    }
		}

        // Actualizar límites de movimiento de los enemigos
        maxX = 0;
        minX = 600;
        for (int i = 0; i < (int)enemigo.size(); i++) {
            for (int j = 0; j < (int)enemigo[i].size(); j++) {
                maxX = max(maxX, (int)enemigo[i][j].Pos().x + 24 * dirEnemigo);
                minX = min(minX, (int)enemigo[i][j].Pos().x + 24 * dirEnemigo);
            }
        }

        // Cambiar dirección de los enemigos si alcanzan los bordes
        if (minX < 24 || maxX > 576) {
            for (int i = 0; i < (int)enemigo.size(); i++) {
                for (int j = 0; j < (int)enemigo[i].size(); j++) {
                    enemigo[i][j].ChangeDir();
                }
            }
            dirEnemigo *= -1;
        }

        // Actualizar enemigos
        for (int i = 0; i < (int)enemigo.size(); i++) {
            for (int j = 0; j < (int)enemigo[i].size(); j++) {
                enemigo[i][j].Update();
            }
        }

        // Renderizado
        window.clear();
        window.draw(nave);

        // Dibujar balas
        for (int i = 0; i < (int)balasNave.size(); i++) {
            window.draw(balasNave[i]);
        }

        // Dibujar enemigos
        for (int i = 0; i < (int)enemigo.size(); i++) {
            for (int j = 0; j < (int)enemigo[i].size(); j++) {
                window.draw(enemigo[i][j]);
            }
        }

        window.display();
    }

    return 0;
}

