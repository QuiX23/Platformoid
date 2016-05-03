#include "Player.h"

Player::Player(int playerNumber)
{
	float score=0;
	bool alive=true;
	moveLeft=false;
	moveRight=false;
	this->playerNumber=playerNumber;
	this->racket=new Racket(playerNumber);
	this->setOfBlocks= new SetOfBlocks(playerNumber);
}

void Player::ifLives(){
	alive=false;
	for (int i=0;i<25;i++){
			if (setOfBlocks->livesTab[i]==true)
				alive=true;
	}
}
void Player::update(Time deltaTime){
	if (alive){
		if(moveLeft)
			racket->moveLeft(deltaTime);
		if(moveRight)
			racket->moveRight(deltaTime);
	}
}

void Player::draw(RenderWindow* window){

	ifLives();
	racket->draw(window);
	setOfBlocks->draw(window);
}