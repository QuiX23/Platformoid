#include "Block.h"

Block::Block(float x,float y,int playerNumber)
{
	width=76;
	length=16;
	lives=true;
	this->playerNumber=playerNumber;
	switch (playerNumber){
		case 1:
			orientation=HORDOWN;
			this->x=x;
			this->y=y;
			rectangle=RectangleShape(Vector2f(width,length));
			rectangle.setPosition(x-width/2, y-length/2);
			break;
		case 2:
			orientation=HORUP;
			this->x=x;
			this->y=y;
			rectangle=RectangleShape(Vector2f(width,length));
			rectangle.setPosition(x-width/2, y-length/2);
			break;
		case 3:
			orientation=VERTLEFT;
			this->x=x;
			this->y=y;
			rectangle=RectangleShape(Vector2f(length,width));
			rectangle.setPosition(x-length/2, y-width/2);
			break;
		case 4:
			orientation=VERTRIGHT;
			this->x=x;
			this->y=y;
			rectangle=RectangleShape(Vector2f(length,width));
			rectangle.setPosition(x-length/2, y-width/2);
			break;
	}
	
	rectangle.setFillColor(Color::Red);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color::White);
}
Block::Block(void)
{
}

float Block::hitRatio(float x,float y){
	if (intersect(x,y)){
		if(orientation==HORUP||orientation==HORDOWN)
			return (x-(this->x))/(width/2);
		else if(orientation==VERTLEFT||orientation==VERTRIGHT)
			return (y-(this->y))/(length/2);
	}
	else
		return -2;
}
