#pragma once
#include "myrectangle.h"
class Block :
	public MyRectangle
{
public:
	bool lives;
	Block(void);
	Block(float x,float y,int playerNumber);
	float hitRatio(float x,float y);
};

