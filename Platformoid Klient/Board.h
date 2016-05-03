#pragma once
#include <SFML/Graphics.hpp>
#include "MyRectangle.h"
using namespace sf;

class Board
{
public:
	RectangleShape boundaries[8];
	void draw(RenderWindow* window);
	Board();
	~Board(void);
};

