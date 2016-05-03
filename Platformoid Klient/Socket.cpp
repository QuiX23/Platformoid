#include "Socket.h"
#include <stdio.h>

void Socket::Init(string ip_adress)
{
	//inicjalizacja
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Blad przy inicjalizacji : %d",WSAGetLastError());
		//exit(EXIT_FAILURE);
	} 
	else
		printf("Zainicjalizowano.\n");

	//tworze socket
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("Blad przy tworzeniu socketu : %d" , WSAGetLastError());
		//exit(EXIT_FAILURE);
	}

	//wypelniam structury
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	//si_other.sin_addr.S_un.S_addr = inet_addr(ip_adress);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
}
//----------------------------------------------------------------------------

void Socket::Send(Player players[4], Ball balls[8])
{
	slen=sizeof(si_other);
	while(1)
	{		
		//na sztywno do testów
		int pl_number=2;
		//wysy³anie numeru gracza
		message[0]=pl_number+'0';
		if (players[0].moveLeft==true){
			message[1]='1';
		}
		else
			message[1]='0';
		if (players[0].moveRight==true){
			message[2]='1';
		}
		else
			message[2]='0';
		message[3]='\0';
		//proba wyslania 
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("Blad przy wysylaniu : %d" , WSAGetLastError());
			break;
			//exit(EXIT_FAILURE);
		}

		memset(buf,'\0', RCVBUFLEN); //czyszcze bufor
		if ((recv_len = recvfrom(s, buf, RCVBUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("Blad przy odbiorze : %d" , WSAGetLastError());
			break;
			//exit(EXIT_FAILURE);
		}
		else {
			printf("Odebrano\n");
			Assign(players,balls);
			break;
		}
	}
}
//----------------------------------------------------------------------------

void Socket::Close()
{
	closesocket(s);
	WSACleanup();
}
//----------------------------------------------------------------------------

void Socket::Assign(Player players[4], Ball balls[8])
{
	for (int i=0;i<4;i++) {
		SetPosition(&players[i]);
		SetTiles(&players[i]);
	}

	for (int i=0;i<buf[184]-'0';i++) {
		SetPosition(&balls[i],185+i*20);
	}
}
//----------------------------------------------------------------------------

float Socket::StringToFloat(string a)
{
	return ::atof(a.c_str());
}
//---------------------------------------------------------------------------

void Socket::SetTiles(Player* player)
{
	int index=(player->playerNumber-1)*46+1;
	for (int i=0;i<25;i++) {
		if (buf[index]=='1') {
			player->setOfBlocks->livesTab[i]=true;
		}
		else {
			player->setOfBlocks->livesTab[i]=false;
		}
		index++;
	}
}
//---------------------------------------------------------------------------

void Socket::SetPosition(Player* pl)
{
	//pobranie pozycji x oraz y
	std::string wspX="",wspY="";
	int i=0;
	//46*nr to indeks gracza, 26 to poprzednie elem tablicy (nr + livesTab), i to kolejna cyfra floata
	char znak = buf[(pl->playerNumber-1)*46+26+i];
	while(znak!='X' && i<10) {
		wspX+=znak;
		i++;
		znak = buf[(pl->playerNumber-1)*46+26+i];
	} 
	i=10;
	znak=buf[(pl->playerNumber-1)*46+26+i];
	while(znak!='X' && i<20) {
		wspY+=znak;
		i++;
		znak = buf[(pl->playerNumber-1)*46+26+i];
	} 
	pl->racket->update(StringToFloat(wspX),StringToFloat(wspY));
}
//---------------------------------------------------------------------------

void Socket::SetPosition(Ball* ball, int index)
{
	//pobranie pozycji x oraz y
	std::string wspX="",wspY="";
	int i=0;
	//46*nr to indeks gracza, 26 to poprzednie elem tablicy (nr + livesTab), i to kolejna cyfra floata
	char znak = buf[index+i];
	while(znak!='X' && i<10) {
		wspX+=znak;
		i++;
		znak = buf[index+i];
	} 
	i=10;
	znak=buf[index+i];
	while(znak!='X' && i<20) {
		wspY+=znak;
		i++;
		znak = buf[index+i];
	} 

	ball->x=StringToFloat(wspX);
	ball->y=StringToFloat(wspY);
}
//---------------------------------------------------------------------------
