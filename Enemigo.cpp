#include "Enemigo.h"

Enemigo::Enemigo(int x, int y,Texture &texture, Vector2f posicionInicial){
	this->posicionInicial = posicionInicial;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(point.x,point.y,8,8));
	sprite.setPosition(x,y);
	sprite.setScale(3,3);
	estado = 0;
	tiempo = 0;
	velocidad=25;
}

void Enemigo::Update(){
	if(tiempo==30){
		sprite.move(velocidad,0);
		estado++;
		estado%=2;
		sprite.setTextureRect(IntRect(point.x+estado*9,point.y,8,8));
		tiempo =0;
	}
	tiempo++;
	
}

void Enemigo::ChangeDir(){
	velocidad*=-1;
	sprite.move(0,abs(velocidad));
}

Vector2f Enemigo::Pos(){
	return sprite.getPosition();
}

void Enemigo::draw(RenderTarget &rt,RenderStates rs) const{
	rt.draw(sprite,rs);
}
