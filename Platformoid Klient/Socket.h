#pragma once

#include<stdio.h>
#include<winsock2.h>
#include "Player.h"
#include "Ball.h"

#pragma comment(lib,"ws2_32.lib")

#define SERVER "192.168.1.102"  //ip 
#define RCVBUFLEN 268  //max dlugosc wiadomosci odbieranej
#define SNDBUFLEN 4  //max dlugosc wiadomosci wysy³anej
#define PORT 50050   //port do nasluchiwania

class Socket
{
private:
	struct sockaddr_in si_other;
	int s, slen;
	char buf[RCVBUFLEN];
	char message[SNDBUFLEN];
	WSADATA wsa;
	int  recv_len;
	void SetPosition(Player *pl);	
	void SetPosition(Ball *ball, int index);
	void SetTiles(Player *player);

public:
	void Init(string ip_adress);
	void Send(Player players[4], Ball balls[8]);
	void Close();

	void Assign(Player players[4], Ball balls[8]);
	float StringToFloat(string a);

};