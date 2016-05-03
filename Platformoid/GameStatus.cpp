#include "GameStatus.h"
#include <sstream>

void GameStatus::Init(Ball balls[8], int ball_count)
{
	//Funkcja wywo³uje siê tylko na pocz¹tku programu dlatego mo¿na bez konsekwencji stworzyæ sobie lokalnie playerów.
	Player player1(1),player2(2),player3(3),player4(4);
	int ind1=0,ind2=46,ind3=92,ind4=138;
	tab[ind1]='1'; //(char)(((int)'0')+player1.playerNumber);
	tab[ind2]='2'; //(char)(((int)'0')+player2.playerNumber);
	tab[ind3]='3'; //(char)(((int)'0')+player3.playerNumber);
	tab[ind4]='4'; //(char)(((int)'0')+player4.playerNumber);
	//zbudowanie klocków dla ka¿dego gracza
	for (int i=1;i<26;i++) {
		tab[i+ind1]=tab[i+ind2]=tab[i+ind3]=tab[i+ind4]='1';
	}
	//zapisanie pozycji ka¿dego gracza
	std::string x=FloatToString(player1.racket->getX());
	std::string y=FloatToString(player1.racket->getY());
	AddPosition(x,y,26+ind1);
	x=FloatToString(player2.racket->getX());
	y=FloatToString(player2.racket->getY());
	AddPosition(x,y,26+ind2);
	x=FloatToString(player3.racket->getX());
	y=FloatToString(player3.racket->getY());
	AddPosition(x,y,26+ind3);
	x=FloatToString(player4.racket->getX());
	y=FloatToString(player4.racket->getY());
	AddPosition(x,y,26+ind4);
	//zapisanie pi³ek
	//ile sztuk jest branych pod uwagê
	tab[184]=ball_count+'0';
	//zapisanie pozycji
	for (int i=0;i<ball_count;i++) {
		x=FloatToString(balls[i].x);
		y=FloatToString(balls[i].y);
		AddPosition(x,y,185+i*20);
	}		
}
//---------------------------------------------------------------------------

string GameStatus::FloatToString(float a)
{
	std::ostringstream x;
	x<<a;
	std::string s(x.str());
	
	for (int i=s.size();i<10;i++) {
		s+="X";
	}
	return s;
}
//---------------------------------------------------------------------------

void GameStatus::AddPosition(string x, string y, int index)
{
	for (int i=0;i<10;i++) {
		tab[index+i]=x[i];
		tab[index+10+i]=y[i];
	}
}
//---------------------------------------------------------------------------

void GameStatus::Receive(char incmsg[],Player players[4],Time deltaTime, Ball balls[8], int ball_count)
{	
	UpdateGame(incmsg[0]-'0',incmsg[1]=='1' ? true:false,incmsg[2]=='1' ? true:false,
				players,deltaTime, balls, ball_count);

	/*SetPosition(&players[0]);
	SetTiles(&players[0]);
	SetPosition(&players[1]);
	SetTiles(&players[1]);
	SetPosition(&players[2]);
	SetTiles(&players[2]);
	SetPosition(&players[3]);
	SetTiles(&players[3]); */
	
}
//---------------------------------------------------------------------------

void GameStatus::SetTiles(Player* player)
{
	int index=(player->playerNumber-1)*46+1;
	for (int i=0;i<25;i++) {
		if (player->setOfBlocks->livesTab[i]==true) {
			tab[index]='1';
		}
		else {
			tab[index]='0';
		}
		index++;
	}
}
//---------------------------------------------------------------------------

void GameStatus::UpdateGame(int pl_number, bool left, bool right, Player players[4],Time deltaTime, Ball balls[8], int ball_count)
{
	//aktualizacja pozycji gracza w tablicy
	if(left) {
		players[pl_number].moveLeft=true;
		players[pl_number].update(deltaTime);		
		players[pl_number].moveLeft=false;
	} 
	else if(right) {
		players[pl_number].moveRight=true;
		players[pl_number].update(deltaTime);		
		players[pl_number].moveRight=false;
	}	
	std::string x=FloatToString(players[pl_number].racket->getX());
	std::string y=FloatToString(players[pl_number].racket->getY());
	AddPosition(x,y,26+46*(players[pl_number].playerNumber-1));

	for (int i=0;i<4;i++) {
		SetTiles(&players[i]);
	}

	//aktualizacja pozycji pi³ek w tablicy
	for (int i=0;i<ball_count;i++) {
		std::string x=FloatToString(balls[i].x);
		std::string y=FloatToString(balls[i].y);
		AddPosition(x,y,185+i*20);
	}
	
}
//---------------------------------------------------------------------------

float GameStatus::StringToFloat(string a)
{
	return ::atof(a.c_str());
}
//---------------------------------------------------------------------------

void GameStatus::SetPosition(Player* pl)
{
	//pobranie pozycji x oraz y
	std::string wspX="",wspY="";
	int i=0;
	//46*nr to indeks gracza, 26 to poprzednie elem tablicy (nr + livesTab), i to kolejna cyfra floata
	char znak = tab[(pl->playerNumber-1)*46+26+i];
	while(znak!='X' && i<10) {
		wspX+=znak;
		i++;
		znak = tab[(pl->playerNumber-1)*46+26+i];
	} 
	i=10;
	znak=tab[(pl->playerNumber-1)*46+26+i];
	while(znak!='X' && i<20) {
		wspY+=znak;
		i++;
		znak = tab[(pl->playerNumber-1)*46+26+i];
	}
	pl->racket->update(StringToFloat(wspX),StringToFloat(wspY));
	//pl->racket->x=StringToFloat(wspX);
	//pl->racket->y=StringToFloat(wspY);
}
//---------------------------------------------------------------------------