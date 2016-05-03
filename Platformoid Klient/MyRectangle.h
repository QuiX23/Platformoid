#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class MyRectangle
{
protected:



public:
	enum type{VERTLEFT,VERTRIGHT,HORUP,HORDOWN};
	RectangleShape rectangle;
	float x,y;
	float width, length;
	int playerNumber;
	type orientation;
	MyRectangle(void);
	bool intersect(float x,float y);
	void draw(RenderWindow* window);
	
};

