#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Nivel.h"
#include "Bala.h"
#include "Nave.h"
#include "Enemigo.h"

using namespace std;
using namespace sf;

Nivel::Nivel(Texture &texture, RenderWindow &window, Font font) 
    : texture(texture), window(window), font(font), currentLevel(1) {
    
}

void Nivel::initiator() {
	while (window.isOpen()) {
		if (this->currentLevel == 1) {
			if (this->firstLevel()) {
				this->currentLevel = 2;
			}
		} else if (this->currentLevel == 2) {
			if (this->secondLevel()) {
				this->currentLevel = 3;
			}
		} else if (this->currentLevel == 3) {
			if (this->thirdLevel()) {
				//mensaje de finalizado
				break;
			}
		}
	}
}

//metodos privados
void Nivel::buildCharacters() {
    this->nave = Nave(288, 555, this->texture);
    
    int enemyWidth = 24;
    int enemyHeight = 24;
    int spacing = 10;

    // Cálculo del punto de inicio para centrar
    float totalWidth = 8 * (enemyWidth + spacing) - spacing;
    float totalHeight = 8 * (enemyHeight + spacing) - spacing;
    float startX = (this->window.getSize().x - totalWidth) / 2;
    float startY = (this->window.getSize().y - totalHeight) / 2;

    // Ajuste para mover los enemigos más abajo en la pantalla
    startY -= 150;

    // Crear enemigos en una matriz 4x8
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            float x = startX + j * (enemyWidth + spacing);
            float y = startY + i * (enemyHeight + spacing);
            this->enemigos.push_back(Enemigo(x, y, this->texture, Vector2f(0, 0)));
        }
    }
}

bool Nivel::firstLevel() {
    bool completedLevel = false;
    vector<Bala> balas;
    
    this->enemigos.clear();
    this->buildCharacters();

    while (this->window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                this->window.close();
                return false;
            }
        }

        nave.update();

        // Manejo del disparo
        if (nave.disparo()) {
            // Crear la bala justo encima de la nave
            balas.push_back(Bala(nave.posicion().x + 24, nave.posicion().y - 24, this->texture, IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), -5));
        }
		
		bool cambiarDireccion = false; // Bandera para indicar si se debe cambiar de dirección

        // Actualizar la posición de los enemigos y verificar límites
        for (size_t i = 0; i < this->enemigos.size(); ++i) {
            Enemigo &enemigo = this->enemigos[i];
            enemigo.Update(0);

            // Verificar colisión con la nave
            if (enemigo.getSprite().getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
                // Colisión detectada: el jugador pierde
                std::cout << "¡Perdiste!" << std::endl;
                return false; // Salir del juego o reiniciar el nivel
            }

            // Verificar colisión con los límites de la ventana
            if (enemigo.Pos().x <= 0 || enemigo.Pos().x + enemigo.getSprite().getGlobalBounds().width >= window.getSize().x) {
                cambiarDireccion = true; // Marcar que debemos cambiar de dirección
                break; // Salir del bucle si se detecta un límite
            }
        }

        // Si se detecta que se debe cambiar de dirección, actualiza todos los enemigos
        if (cambiarDireccion) {
            for (size_t i = 0; i < this->enemigos.size(); ++i) {
                this->enemigos[i].ChangeDir(); // Cambiar dirección de todos los enemigos
            }
        }
		
        // Actualizar y eliminar balas
        for (vector<Bala>::iterator it = balas.begin(); it != balas.end();) {
		    it->update();
		
		    // Verificar si la bala sale de la ventana
		    if (it->getPos().y < 0) {
		        it = balas.erase(it);
		    } else {
		        // Verificar colisión con enemigos
		        bool hit = false;
		        for (vector<Enemigo>::iterator enemyIt = this->enemigos.begin(); enemyIt != this->enemigos.end();) {
		            if (it->getGlobalBounds().intersects(enemyIt->getSprite().getGlobalBounds())) {
		                enemyIt = this->enemigos.erase(enemyIt);
		                hit = true;
		                break;
		            } else {
		                ++enemyIt;
		            }
		        }
		        // Si se golpeó un enemigo, eliminar la bala
		        if (hit) {
		            it = balas.erase(it);
		        } else {
		            ++it;
		        }
		    }
		}

        // Limpiar la ventana
        this->window.clear();

        // Dibujar la nave y los enemigos
        this->nave.draw(this->window, RenderStates::Default);
        for (size_t i = 0; i < this->enemigos.size(); ++i) {
            this->enemigos[i].draw(this->window, RenderStates::Default);
        }

        // Dibujar las balas
        for (size_t i = 0; i < balas.size(); i++) {
            balas[i].draw(this->window, RenderStates::Default);
        }

        // Verificar si todos los enemigos han sido eliminados
        if (this->enemigos.empty()) {
            completedLevel = true;
            break;
        }

        // Mostrar el contenido de la ventana
        this->window.display();
    }

    return completedLevel;
}

bool Nivel::secondLevel() {
    
}

bool Nivel::thirdLevel() {
	bool completedLevel = false;
    vector<Bala> balas; // Balas de la nave
    vector<Bala> balasEnemigos; // Balas disparadas por los enemigos

    this->enemigos.clear();
    this->buildCharacters(); // Inicializa enemigos

    const size_t N = 8; // Número de enemigos en la última fila
    float deltaTime = clock.restart().asSeconds();
    float enemyShootCooldown = 1.0f; // Tiempo de recarga para disparos enemigos
    float enemyShootTimer = 0.0f; // Temporizador para disparos enemigos

    while (this->window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                this->window.close();
                return false; // Cierra el juego
            }
        }

        nave.update(); // Actualiza la posición de la nave

        // Manejo del disparo
        if (nave.disparo()) {
            // Crear la bala justo encima de la nave
            balas.push_back(Bala(nave.posicion().x + 24, nave.posicion().y - 24, this->texture, IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), -5));
        }

        bool cambiarDireccion = false; // Bandera para cambio de dirección

        // Actualizar enemigos y verificar colisiones
        for (size_t i = 0; i < this->enemigos.size(); ++i) {
            Enemigo &enemigo = this->enemigos[i];
            enemigo.Update(deltaTime); // Mueve el enemigo

            // Verificar colisión con la nave
            if (enemigo.getSprite().getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
                std::cout << "¡Perdiste!" << std::endl;
                return false; // Colisión: el jugador pierde
            }

            // Verificar límites de la ventana
            if (enemigo.Pos().x <= 0 || enemigo.Pos().x + enemigo.getSprite().getGlobalBounds().width >= window.getSize().x) {
                cambiarDireccion = true; // Cambiar dirección
                break; // Salir del bucle al detectar un límite
            }
        }

        // Si se detecta que se debe cambiar de dirección, actualiza todos los enemigos
        if (cambiarDireccion) {
            for (size_t i = 0; i < this->enemigos.size(); ++i) {
                this->enemigos[i].ChangeDir(balasEnemigos, texture); // Solo cambiar dirección
            }
        }

        // Actualizar disparos de enemigos
        enemyShootTimer += deltaTime; // Aumentar el temporizador de disparo
        if (enemyShootTimer >= enemyShootCooldown) {
            enemyShootTimer = 0.0f; // Reiniciar el temporizador

            // Disparar desde la última fila de enemigos si no hay balas en pantalla
            for (size_t i = 0; i < this->enemigos.size(); ++i) {
                if (this->enemigos[i].isInLastRow(this->enemigos.size(), N)) { // Verifica si está en la última fila
                    bool hayBalasEnPantalla = false;
                    for (size_t j = 0; j < balasEnemigos.size(); ++j) {
					    const Bala& bala = balasEnemigos[j];
					    if (bala.getPos().y >= 0) { // Verifica si hay balas de enemigos en pantalla
					        hayBalasEnPantalla = true;	
					        break; // Salir del bucle si encontramos una bala en pantalla
					    }
					}
                    if (!hayBalasEnPantalla) {
                        balasEnemigos.push_back(Bala(enemigos[i].Pos().x + 16, enemigos[i].Pos().y + 24, this->texture,
                                    IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), 5));
                    }
                }
            }
        }

        // Actualizar y eliminar balas
        for (vector<Bala>::iterator it = balas.begin(); it != balas.end();) {
            it->update(); // Actualiza posición de la bala

            // Verificar si la bala sale de la ventana
            if (it->getPos().y < 0) {
                it = balas.erase(it); // Eliminar bala si está fuera de la ventana
            } else {
                // Verificar colisión con enemigos
                bool hit = false;
                for (vector<Enemigo>::iterator enemyIt = this->enemigos.begin(); enemyIt != this->enemigos.end();) {
                    if (it->getGlobalBounds().intersects(enemyIt->getSprite().getGlobalBounds())) {
                        enemyIt = this->enemigos.erase(enemyIt); // Eliminar enemigo si es golpeado
                        hit = true; // Se ha golpeado un enemigo
                        break; // Salir del bucle para evitar múltiples eliminaciones
                    } else {
                        ++enemyIt; // Solo incrementar si no se eliminó el enemigo
                    }
                }
                // Si se golpeó un enemigo, eliminar la bala
                if (hit) {
                    it = balas.erase(it);
                } else {
                    ++it; // Solo incrementar si no se eliminó
                }
            }
        }

        // Actualizar y eliminar balas de enemigos
        for (vector<Bala>::iterator it = balasEnemigos.begin(); it != balasEnemigos.end();) {
            it->update(); // Actualiza posición de la bala de enemigo

            // Verificar si la bala de enemigo sale de la ventana
            if (it->getPos().y > window.getSize().y) {
                it = balasEnemigos.erase(it); // Eliminar si sale de la ventana
            } else {
                // Verificar colisión con la nave
                if (it->getGlobalBounds().intersects(nave.getSprite().getGlobalBounds())) {
                    std::cout << "¡Perdiste!" << std::endl;
                    return false; // Colisión: el jugador pierde
                } else {
                    ++it; // Solo incrementar si no se eliminó
                }
            }
        }

        // Limpiar la ventana
        this->window.clear();

        // Dibujar la nave y los enemigos
        this->nave.draw(this->window, RenderStates::Default);
        for (size_t i = 0; i < this->enemigos.size(); ++i) {
            this->enemigos[i].draw(this->window, RenderStates::Default);
        }

        // Dibujar balas de la nave
        for (size_t i = 0; i < balas.size(); ++i) {
            balas[i].draw(this->window, RenderStates::Default);
        }

        // Dibujar balas de los enemigos
        for (size_t i = 0; i < balasEnemigos.size(); ++i) {
            balasEnemigos[i].draw(this->window, RenderStates::Default);
        }

        // Verificar si todos los enemigos han sido eliminados
        if (this->enemigos.empty()) {
            completedLevel = true; // Nivel completado
            break; // Salir del bucle
        }

        // Mostrar el contenido de la ventana
        this->window.display();
    }

    return completedLevel; // Retorna si el nivel se completó
}
