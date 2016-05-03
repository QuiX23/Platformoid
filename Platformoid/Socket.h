#pragma once

#include <winsock2.h>
#include "GameStatus.h"

#pragma comment(lib,"ws2_32.lib")
 
#define RCVBUFLEN 5  //max dlugosc wiadomosci odbieranej
#define SNDBUFLEN 268 //max d³ugoœæ wiadomoœci wysy³anej
#define PORT 50050   //port
#define SERVER "192.168.1.102" //adres ip

class Socket
{
private:
	SOCKET s; //tworzymy socket
    struct sockaddr_in server, si_other; //tworzymy structury do obslugi
    int slen, recv_len;
    char buf[SNDBUFLEN];
    WSADATA wsa; //fundament 

public:
	void Init(string ip_adress);
	void Listen(GameStatus *game,Player players[],Time deltaTime, Ball balls[8], int ball_count);
	void Close();


	
};