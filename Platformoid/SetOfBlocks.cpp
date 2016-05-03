#include "SetOfBlocks.h"

SetOfBlocks::SetOfBlocks(int playerNumber)
{
	this->playerNumber=playerNumber;
	if(playerNumber== 1){
		float x=240,y=780;
		for (int i=0;i<5;i++){
			for (int i=0;i<5;i++){
				set.push_back(*(new Block(x,y,playerNumber)));
				x+=80;
			}
			x=240;
			y-=20;
		}
	}
	else if(playerNumber== 2){
		float x=240,y=20;
		for (int i=0;i<5;i++){
			for (int i=0;i<5;i++){
				set.push_back(*(new Block(x,y,playerNumber)));
				x+=80;
			}
			x=240;
			y+=20;
		}
	}
	else if(playerNumber== 3){
		float x=20,y=240;
		for (int i=0;i<5;i++){
			for (int i=0;i<5;i++){
				set.push_back(*(new Block(x,y,playerNumber)));
				y+=80;
			}
			y=240;
			x+=20;
		}

	}
	else if(playerNumber== 4){
		float x=780,y=240;
		for (int i=0;i<5;i++){
			for (int i=0;i<5;i++){
				set.push_back(*(new Block(x,y,playerNumber)));
				y+=80;
			}
			y=240;
			x-=20;
		}


	}
	for (int i=0;i<25;i++)
		livesTab[i]=true;
}

void SetOfBlocks::draw(RenderWindow* window){
	for (int i=0;i<set.size();i++)
		if (livesTab[i])
			set[i].draw(window);
	
}

float SetOfBlocks::hitRatio(float x,float y){
	for (int i=0;i<set.size();i++){
		if (set[i].lives&&set[i].intersect(x,y))
		{
			float r=set[i].hitRatio(x,y);
			set[i].lives=false;
			livesTab[i]=false;
			return r;
		}
	}
	return -2;
}





