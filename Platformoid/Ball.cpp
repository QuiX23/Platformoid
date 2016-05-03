#include "Ball.h"



Ball::Ball(void)
{
	speed=300;
	x=400;
	y=400;
	angle=45;
	ballSize=10;
	circle.setRadius(ballSize);
	//circle.setOutlineThickness(3);
	//circle.setOutlineColor(Color::Red);
	circle.setFillColor(Color::Cyan);
	circle.setOrigin(ballSize,ballSize);
}
Ball::Ball(float x_poz,float y_poz)
{
	speed=300;
	x=x_poz;
	y=y_poz;

	angle=45;

	ballSize=10;
	circle.setRadius(ballSize);	
	//circle.setOutlineThickness(2);	
	//circle.setOutlineColor(Color::Red);
	circle.setOrigin(ballSize,ballSize);
	circle.setFillColor(Color::Cyan);
}
Ball::Ball(float x_poz,float y_poz,float angle_new)
{
	speed=300;
	x=x_poz;
	y=y_poz;
	angle=angle_new;
	ballSize=10;
	circle.setRadius(ballSize);
	//circle.setOutlineThickness(3);
	//circle.setOutlineColor(Color::Red);
	circle.setFillColor(Color::Cyan);
	circle.setOrigin(ballSize,ballSize);
}
Ball::~Ball(void)
{
}

void Ball::draw(RenderWindow* window)
{
	circle.setPosition(x,y);
	window->draw(circle);
}

float Ball::angleDistance(float angle1,float angle2)
{
	float anwser;

	if (angle1>angle2)
		anwser=angle1-angle2;
	else
		anwser=angle2-angle1;

	if(anwser>180)
		return 360-anwser;
	else
		return anwser;
	
}

float Ball::Bounce(float offsetX,float offsetY,float rocketOffset,bool forward,bool corner)
{
	float alfa;
	if(offsetX>0 && offsetY>0)
		alfa = fmod((radToDeg(atan(offsetX/offsetY))+360),360);
	else if (offsetX>0 && offsetY<0)
	{
		alfa = fmod((radToDeg(atan(offsetX/offsetY))+180),360);
	}
	else if (offsetX<0 && offsetY<0)
	{
		alfa = fmod((radToDeg(atan(offsetX/offsetY))+180),360);
	}
	else if (offsetX<0 && offsetY>0)
	{
		alfa = fmod((radToDeg(atan(offsetX/offsetY))+360),360);
	}
	else if (offsetX>0 && offsetY==0)
	{
		alfa=90;
	}
	else if (offsetX<0 && offsetY==0)
	{
		alfa=270;
	}
	else if (offsetX==0 && offsetY>0)
	{
		alfa=0;
	}
	else if (offsetX==0 && offsetY<0)
	{
		alfa=180;
	}
	if(forward)
	{
		if(angleDistance(angle,alfa)>=90)
			return angle;
	}

	float wallAngle=fmod(alfa+270,360);//k¹t nachylenia œciany w któr¹ urerzy³a pi³ka
	
	float incomAnglle=fmod(90-(angle-alfa)+720,360)*(rocketOffset);//k¹t padania wzglêdem œciany
	return fmod(180+incomAnglle+wallAngle,360);

}

Vector2f Ball::isBallColision(FloatRect &kolizja)
{
	float radius = circle.getRadius()+circle.getOutlineThickness();
	float offsetX,offsetY,collisionPointX,collisionPointY,distance;
	offsetX = (kolizja.left+(kolizja.width/2))-x;
	offsetY = -((kolizja.top+(kolizja.height/2))-y);
	if(offsetX==0 && offsetY>0)
	{
		return Vector2f(0,radius);
	}
	else if(offsetX==0 && offsetY<0)
	{
		return Vector2f(0,-radius);
	}
	else if(offsetX<0 && offsetY==0)
	{
		return Vector2f(-radius,0);
	}
	else if(offsetX>0 && offsetY==0)
	{
		return Vector2f(radius,0);
	}
	else if(offsetX>0 && offsetY>0)
	{
		if(collisionPointX=kolizja.left<x)
			return Vector2f(0,radius);
		else if(kolizja.top+kolizja.height>y)
			return Vector2f(radius,0);
		else
		{
			collisionPointX=kolizja.left;
			collisionPointY=kolizja.top+kolizja.height;
		}
	}
	else if(offsetX<0 && offsetY>0)
	{
		if(kolizja.left+kolizja.width>x)
			return Vector2f(0,radius);
		else if(kolizja.top+kolizja.height>y)
			return Vector2f(-radius,0);
		else
		{
			collisionPointX=kolizja.left+kolizja.width;
			collisionPointY=kolizja.top+kolizja.height;
		}
	}
	else if(offsetX>0 && offsetY<0)
	{
		if(kolizja.left<x)
			return Vector2f(0,-radius);
		else if(kolizja.top<y)
			return Vector2f(radius,0);
		else
		{
			collisionPointX=kolizja.left;
			collisionPointY=kolizja.top;
		}
	}
	else if(offsetX<0 && offsetY<0)
	{
		if(kolizja.left+kolizja.width>x)
			return Vector2f(0,-radius);
		else if(kolizja.top<y)
			return Vector2f(-radius,0);
		else
		{
			collisionPointX=kolizja.left+kolizja.width;
			collisionPointY=kolizja.top;
		}
	}
	offsetX = collisionPointX-x;//zmiana offsetów, od teraz nie wskazuj¹ odleg³oœci do œrodka "kwadratu nachodzenia" tylko odleg³oœæ punktu tego kwadratu który jest najbli¿szy pi³ce
	offsetY = -(collisionPointY-y);
	distance=sqrt((offsetX*offsetX)+(offsetY*offsetY));
	if(distance<radius)
		return Vector2f(offsetX,offsetY);
	else
		return Vector2f(0,0);
}

int Ball::kollision(Player players[4],RenderWindow* window,Board board)
{
	bool ret=false;
	bool isCollisionWythRacket=false;
	for(int i = 0 ; i<4 ; i++)
	{
		FloatRect kolizja = FloatRect();
		
		for(int j=0;j<25;j++)
		{
			if(players[i].setOfBlocks->livesTab[j] && players[i].setOfBlocks->set[j].rectangle.getGlobalBounds().intersects(circle.getGlobalBounds(),kolizja))
			{
				Vector2f collision = isBallColision(kolizja);
				if(collision!=Vector2f(0,0))
				{
					angle =Bounce(collision.x,collision.y,1,1,0);;
					ret = true;
					players[i].setOfBlocks->livesTab[j]=false;
				}
			}
		}
		if(players[i].racket->rectangle.getGlobalBounds().intersects(circle.getGlobalBounds(),kolizja))
		{
			Vector2f collision = isBallColision(kolizja);
			if(collision!=Vector2f(0,0))
			{
				if(wasCollisionWithRacket==false)
				{
					float rocketOffsetx=collision.x+x;
					float rocketOffsety=-collision.y+y;
					bool corner=false;
					float hitRatio=players[i].racket->hitRatio(rocketOffsetx,rocketOffsety);
					if(hitRatio==3 || hitRatio==-3 || hitRatio==-4 )
						hitRatio=1;
					else if (hitRatio==2 || hitRatio==-2)
					{
						hitRatio=1;
						//hitRatio/=2.5;
						//hitRatio+=1;
						corner=true;
					}
					else
					{
						hitRatio/=1.5;
						hitRatio+=1;
					}
					angle = Bounce(collision.x,collision.y,hitRatio,1,corner);
					ret=true;
					wasCollisionWithRacket=true;
				}
				isCollisionWythRacket=true;
			}
		}
	}
	for(int i = 0 ; i<8 ; i++)
	{
		FloatRect kolizja = FloatRect();
		if (circle.getGlobalBounds().intersects(board.boundaries[i].getGlobalBounds(),kolizja))
		{
			Vector2f collision = isBallColision(kolizja);
			if(collision!=Vector2f(0,0))
			{
				float offsetX,offsetY;
				offsetX = (kolizja.left+(kolizja.width/2))-x;
				offsetY = -((kolizja.top+(kolizja.height/2))-y);
				angle = Bounce(offsetX,offsetY,1,1,0);

				ret=true;
			}
		}
	}
	if(isCollisionWythRacket==false)
	{
		wasCollisionWithRacket=false;
	}
	
	return ret;
}

float Ball::radToDeg(float alfa)
{
	return alfa*57.2957795130823208767981548141051703324054724665643;
}

float Ball::degToRad(float alfa)
{
	return alfa*0.01745329251994329576923690768488612713442871888541;
}

void Ball::update(Time deltaTime,Player players[4],RenderWindow* window,Board board)
{
	kollision(players,window,board);

	float offset=speed*deltaTime.asSeconds();//d³ugoœæ o jak¹ przesunie sie ku³ko
	float deltaX = sin((double)degToRad(angle))*offset;
	float deltaY = -(cos((double)degToRad(angle))*offset);

	y += deltaY;
	x += deltaX;

}
