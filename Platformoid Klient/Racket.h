#pragma once
#include "myrectangle.h"
class Racket :
public MyRectangle
{
private:
	float speed;
public:

	Racket(int playerNumber);
	Racket(void);
	
	float hitRatio(float x,float y);
	void moveLeft(Time deltaTime);
	void moveRight(Time deltaTime);	
	void update(float x,float y);
	float getX();
	float getY();
	
};

