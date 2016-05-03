#include <SFML/Graphics.hpp>
#include <iostream>
#include "Socket.h"
#include "Ball.h"
#include "Board.h"

using namespace sf;
using namespace std;

int main()
{
	int playerNumber;
    RenderWindow window(VideoMode(800, 800), "SFML works!");
	Player players[4]={Player(1),Player(2),Player(3),Player(4)};
	Ball balls[8]={Ball(400,400,14),Ball(400,400,95),Ball(400,400,185),Ball(400,400,275),Ball(400,400,46),Ball(400,400,136),Ball(400,400,226),Ball(400,400,316)};
	Board board = Board();

	string ip_adress="";
	std::cout<<"Podaj adres IP serwera\n";
	//std::cin>>ip_adress;

	Socket socket;
	socket.Init(ip_adress);

	while (window.isOpen())
    {
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

		players[0].moveLeft=false;
		players[0].moveRight=false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			players[0].moveLeft=true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			 players[0].moveRight=true;
		}
		
		window.clear();

		board.draw(&window);
		players[0].draw(&window);
		players[1].draw(&window);
		players[2].draw(&window);
		players[3].draw(&window);
		for(int i=0;i<4;i++)
			balls[i].draw(&window);

        window.display();
		
		//nowy w¹tek
		socket.Send(players,balls);
   }
	
	socket.Close();
    return 0;
}