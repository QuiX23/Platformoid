#include "Racket.h"

Racket::Racket(int playerNumber)
{
	width=120;
	length=15;
	this->playerNumber=playerNumber;
	switch (playerNumber){
	case 1:
		orientation=HORDOWN;
		x=400;
		y=620;
		rectangle=RectangleShape(Vector2f(width,length));
		rectangle.setPosition(x-width/2, y-length/2);
		break;
	case 2:
		orientation=HORUP;
		x=400;
		y=180;
		rectangle=RectangleShape(Vector2f(width,length));
		rectangle.setPosition(x-width/2, y-length/2);
		break;
	case 3:
		orientation=VERTLEFT;
		y=400;
		x=180;
		rectangle=RectangleShape(Vector2f(length,width));
		rectangle.setPosition(x-length/2, y-width/2);
		break;
	case 4:
		orientation=VERTRIGHT;
		y=400;
		x=620;
		rectangle=RectangleShape(Vector2f(length,width));
		rectangle.setPosition(x-length/2, y-width/2);
		break;
	}
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setFillColor(Color::Green);
	speed=200;
}
Racket::Racket(void)
{
}

float Racket::hitRatio(float x,float y){//
		/*
		if(orientation==HORUP||orientation==HORDOWN){
			float ratio=(x-(this->x))/(width/2);
			if (orientation==HORUP){
				if (y
			
			}
			else if (orientation==HORDOWN){
			}
			
		}
		else if(orientation==VERTLEFT||orientation==VERTRIGHT){
			float ratio=(y-(this->y))/(length/2);
			return (y-(this->y))/(length/2);
		}
		return -2;
		*/
	if (orientation==HORUP){
		if (x>=(this->x-(width/2)+2)&&x<=(this->x+(width/2)-2)&&y>=(this->y+(length/2)-2)&&y<=(this->y+(length/2))){
			return ((this->x)-x)/(width/2);
		}
		else if(x>=(this->x-width/2)&&x<=(this->x-width/2+2)&&y>=(this->y+(length/2)-2)&&y<=(this->y+(length/2))){
			return 2;
		
		}
		else if(x>=(this->x+width/2-2)&&x<=(this->x+width/2)&&y>=(this->y+(length/2)-2)&&y<=(this->y+(length/2))){
			return -2;
		}
		else if(x>=(this->x-width/2)&&x<=(this->x-width/2+2)&&y>=(this->y-(length/2))&&y<=(this->y+(length/2)-2)){
			return 3;
		
		}
		else if(x>=(this->x+width/2-2)&&x<=(this->x+width/2)&&y>=(this->y-(length/2))&&y<=(this->y+(length/2)-2)){
			return -3;
		}
	}
	else if (orientation==HORDOWN){
		//plasko
		if (x>=(this->x-(width/2)+2)&&x<=(this->x+(width/2)-2)&&y>=(this->y-(length/2)&&y<=(this->y-(length/2)+2))){
			return (x-(this->x))/(width/2);
		}
		//lewy rog
		else if(x>=(this->x-width/2)&&x<=(this->x-width/2+2)&&y<=(this->y-(length/2)+2)&&y>=(this->y-(length/2))){
			return -2;
		
		}
		//prawy rog
		else if(x>=(this->x+width/2-2)&&x<=(this->x+width/2)&&y<=(this->y-(length/2)+2)&&y>=(this->y-(length/2))){
			return 2;
		}
		//lewy bok
		else if(x>=(this->x-width/2)&&x<=(this->x-width/2+2)&&y<=(this->y+(length/2))&&y>=(this->y-(length/2)+2)){
			return -3;
		
		}
		//prawy bok
		else if(x>=(this->x+width/2-2)&&x<=(this->x+width/2)&&y<=(this->y+(length/2))&&y>=(this->y-(length/2)+2)){
			return 3;
		}
	}
	else if (orientation==VERTRIGHT){
		if (y>=(this->y-(width/2)+2)&&y<=(this->y+(width/2)-2)&&x>=(this->x-(length/2))&&x<=(this->x-(length/2)+2)){
			return ((this->y)-y)/(width/2);
		}
		else if(y>=(this->y-(width/2))&&y<=(this->y-(width/2)+2)&&x>=(this->x-(length/2))&&x<=(this->x-(length/2)+2)){
			return 2;
		
		}
		else if(y>=(this->y+(width/2)-2)&&y<=(this->y+(width/2))&&x>=(this->x-(length/2))&&x<=(this->x-(length/2)+2)){
			return -2;
		}
		else if(y>=(this->y-(width/2))&&y<=(this->y-(width/2)+2)&&x>=(this->x-(length/2)+2)&&x<=(this->x+(length/2))){
			return 3;
		
		}
		else if(y>=(this->y+(width/2)-2)&&y<=(this->y+(width/2))&&x>=(this->x-(length/2)+2)&&x<=(this->x+(length/2))){
			return -3;
		}
	}
	else if (orientation==VERTLEFT){
		if (y>=(this->y-(width/2)+2)&&y<=(this->y+(width/2)-2)&&x>=(this->x+(length/2)-2)&&x<=(this->x+(length/2))){
			return (y-(this->y))/(width/2);
		}
		else if(y>=(this->y-(width/2))&&y<=(this->y-(width/2)+2)&&x>=(this->x+(length/2)-2)&&x<=(this->x+(length/2))){
			return -2;
		
		}
		else if(y>=(this->y+(width/2)-2)&&y<=(this->y+(width/2))&&x>=(this->x+(length/2)-2)&&x<=(this->x+(length/2))){
			return 2;
		}
		else if(y>=(this->y-(width/2))&&y<=(this->y-(width/2)+2)&&x<=(this->x+(length/2)-2)&&x>=(this->x-(length/2))){
			return -3;
		}
		else if(y>=(this->y+(width/2)-2)&&y<=(this->y+(width/2))&&x<=(this->x+(length/2)-2)&&x>=(this->x-(length/2))){
			return 3;
		}

	}

	return -4;
}
void Racket::moveLeft(Time deltaTime){
	switch (playerNumber){
	case 1:
		if ((x-width/2)>200){
			x-=speed*deltaTime.asSeconds();
			rectangle.move(-speed*deltaTime.asSeconds(),0);
		}
		break;
	case 2:
		if ((x+width/2)<600){
			x+=speed*deltaTime.asSeconds();
			rectangle.move(+speed*deltaTime.asSeconds(),0);
		}
		break;
	case 3:
		if ((y-width/2)>200){
			y-=speed*deltaTime.asSeconds();
			rectangle.move(0,-speed*deltaTime.asSeconds());
		}
		break;
	case 4:
		if ((y+width/2)<600){
			y+=speed*deltaTime.asSeconds();
			rectangle.move(0,+speed*deltaTime.asSeconds());
		}
		break;
	}
}

void Racket::moveRight(Time deltaTime){
	switch (playerNumber){
	case 1:
		if ((x+width/2)<600){
			x+=speed*deltaTime.asSeconds();
			rectangle.move(speed*deltaTime.asSeconds(),0);
		}
		break;
	case 2:
		if ((x-width/2)>200){
			x-=speed*deltaTime.asSeconds();
			rectangle.move(-speed*deltaTime.asSeconds(),0);
		}
		break;
	case 3:
		if ((y+width/2)<600){
			y+=speed*deltaTime.asSeconds();
			rectangle.move(0,speed*deltaTime.asSeconds());
		}
		break;
	case 4:
		if ((y-width/2)>200){
			y-=speed*deltaTime.asSeconds();
			rectangle.move(0,-speed*deltaTime.asSeconds());
		}
		break;
	}
}

void Racket::update(float x,float y) {
	if (playerNumber==1||playerNumber==2)
		rectangle.setPosition(x-width/2, y-length/2);
	else if (playerNumber==3||playerNumber==4)
		rectangle.setPosition(x-length/2, y-width/2);
}

float Racket::getY()
{
	return this->y;
}

float Racket::getX()
{
	return this->x;
}