#pragma once
#include "Racket.h"
#include "SetOfBlocks.h"
#include <SFML/Graphics.hpp>
#include <string>

class Player
{
public:
	int playerNumber;
	Racket* racket;
	SetOfBlocks* setOfBlocks;
	float score;
	string nazwa;
	bool alive;
	
	void ifLives(void);
	Player(void);
	Player(int PlayerNumber);
	void update(Time deltaTime);
	bool moveLeft,moveRight;
	void draw(RenderWindow* window);
};

