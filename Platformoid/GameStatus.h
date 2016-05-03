#pragma once

#include "Player.h"
#include "Ball.h"

class GameStatus
{
private:
	
	string FloatToString(float a);
	void AddPosition(string x, string y, int index);
	void SetPosition(Player *pl);
	void SetTiles(Player *player);
public:
	void UpdateGame(int pl_number, bool left, bool right,Player players[],Time deltaTime, Ball balls[8], int ball_count); // zmiana stanu gry na podstawie informacji o ruchu gracza
	char tab[265];//(1- numerGracza + 25-klocki + 10-x + 10-y )*4graczy	+ iloœæ pi³ek(index:184) + 8*10 - wsp pi³ek
	float StringToFloat(string a);
	void Init(Ball balls[8], int ball_count);
	void Receive(char incmsg[],Player players[],Time deltaTime, Ball balls[8], int ball_count);//3 znaki - nr + lewo + prawo
}; 