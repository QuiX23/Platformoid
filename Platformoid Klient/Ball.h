#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Player.h"
#include "Board.h"
#include "MyRectangle.h"
using namespace sf;
class Ball
{
protected:
	bool wasCollisionWithRacket;
	float degToRad(float alfa);
	float radToDeg(float alfa);
	int kollision(Player players[4],RenderWindow* window,Board board);
	float Bounce(float offsetX,float offsetY,float rocketOffset,bool forward,bool corner);
	Vector2f isBallColision(FloatRect &kolizja);
	float angleDistance(float angle1,float angle2);
public:
	int ballSize;
	CircleShape circle;
	float speed;
	float x,y;
	float angle;
	Ball(void);
	Ball(float x,float y);
	Ball(float x,float y,float angle);
	~Ball(void);
	void update(Time deltaTime,Player players[4],RenderWindow* window,Board board);
	void draw(RenderWindow* window);
};

