#include "Board.h"


Board::Board()
{
	boundaries[0]=RectangleShape(Vector2f(10,810));//lewo
	boundaries[0].setPosition(-10,0);
	boundaries[1]=RectangleShape(Vector2f(10,810));//prawo
	boundaries[1].setPosition(800,-10);
	boundaries[2]=RectangleShape(Vector2f(810,10));//góra
	boundaries[2].setPosition(-10,-10);
	boundaries[3]=RectangleShape(Vector2f(810,10));//dó³
	boundaries[3].setPosition(0,800);

	boundaries[4]=RectangleShape(Vector2f(180,180));
	boundaries[4].setPosition(0,0);
	boundaries[4].setOutlineThickness(10);
	boundaries[4].setFillColor(Color::Black);
	boundaries[4].setOutlineColor(Color::Blue);

	boundaries[5]=RectangleShape(Vector2f(180,180));
	boundaries[5].setPosition(0,620);
	boundaries[5].setOutlineThickness(10);
	boundaries[5].setFillColor(Color::Black);
	boundaries[5].setOutlineColor(Color::Blue);

	boundaries[6]=RectangleShape(Vector2f(180,180));
	boundaries[6].setPosition(620,0);
	boundaries[6].setOutlineThickness(10);
	boundaries[6].setFillColor(Color::Black);
	boundaries[6].setOutlineColor(Color::Blue);

	boundaries[7]=RectangleShape(Vector2f(180,180));
	boundaries[7].setPosition(620,620);
	boundaries[7].setOutlineThickness(10);
	boundaries[7].setFillColor(Color::Black);
	boundaries[7].setOutlineColor(Color::Blue);

}


void Board::draw(RenderWindow* window)
{
	for(int i=4;i<8;i++)
	{
		window->draw(boundaries[i]);
	}
}

Board::~Board(void)
{
}
