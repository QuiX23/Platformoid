#include <SFML/Graphics.hpp>
#include <iostream>
#include "Socket.h"
#include "Ball.h"
#include "Board.h"

using namespace sf;
using namespace std;

int main()
{
	int ball_count=4;
    RenderWindow window(VideoMode(800, 800), "SFML works!");
	Player players[4]={Player(1),Player(2),Player(3),Player(4)};
	Ball balls[8]={Ball(400,400,14),Ball(400,400,95),Ball(400,400,185),Ball(400,400,275),Ball(400,400,46),Ball(400,400,136),Ball(400,400,226),Ball(400,400,316)};
	Board board = Board();


    Clock clock;
	Time time=clock.getElapsedTime();;
	Time deltaTime=clock.getElapsedTime();;


	GameStatus game;
	Socket socket;

	string ip_adress="";
	std::cout<<"Podaj adres IP \n";
	//std::cin>>ip_adress;

	game.Init(balls,ball_count);
	socket.Init(ip_adress);

	
	while (window.isOpen())
    {
		deltaTime= clock.getElapsedTime();
		deltaTime-=time;
		time = clock.getElapsedTime();
		//cout <<deltaTime.asSeconds()<<endl;
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
	    
		

		players[0].update(deltaTime);
		players[1].update(deltaTime);
		players[2].update(deltaTime);
		players[3].update(deltaTime);
		for(int i=0;i<ball_count;i++)
			balls[i].update(deltaTime,players,&window,board);

		window.clear();

		board.draw(&window);
		players[0].draw(&window);
		players[1].draw(&window);
		players[2].draw(&window);
		players[3].draw(&window);
		for(int i=0;i<ball_count;i++)
			balls[i].draw(&window);

        window.display();

		socket.Listen(&game,players,deltaTime, balls, ball_count);

   }
	socket.Close();
    return 0;
}