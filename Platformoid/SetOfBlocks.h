#pragma once
#include "Block.h"
#include <vector>
using namespace std;

class SetOfBlocks
{
public:
	int playerNumber;
	vector <Block> set;
	bool livesTab[25];
	SetOfBlocks(int playerNumber);
	void draw(RenderWindow* window);
	float hitRatio(float x,float y);
	
};

