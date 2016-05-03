#include "Socket.h"
#include <stdio.h>

void Socket::Init(string ip_adress)
{
	slen = sizeof(si_other);

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Blad : %d",WSAGetLastError());
        //exit(EXIT_FAILURE);
    } 
	else
		printf("Zainicjalizowano.\n");

	//tworzenie socketu
    if((s = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP )) == INVALID_SOCKET)
    {
        printf("Blad przy tworzeniu socketa : %d" , WSAGetLastError());
    }
	else
		printf("Socket utworzony.\n");

	//wypelnianie structury dla socketu
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );
	//si_other.sin_addr.S_un.S_addr = inet_addr(ip_adress);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
     
    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Blad przy bindowaniu : %d" , WSAGetLastError());
        //exit(EXIT_FAILURE);
    }
	else
		puts("Bindowanie - sukces");

}
//----------------------------------------------------------------------------

void Socket::Listen(GameStatus *game,Player players[],Time deltaTime, Ball balls[8], int ball_count) 
{
	//nasluchiwanie
    while(1)
    {
        printf("Czekam...");
        fflush(stdout);
         
        
        memset(buf,'\0', RCVBUFLEN);//czyszcze buffor na wszelki
         
        //proba odbioru wiadomosci - recv czeka na wiadomosc 
        if ((recv_len = recvfrom(s, buf, RCVBUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
        {
            printf("Blad przy odbiorze wiadomosci : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
        } else
			//jezeli odebrano wiadomosc 
			printf("Odebrano\n");

		//wewn¹trz receive dzieje siê ca³y update
        game->Receive(buf,players,deltaTime, balls, ball_count);


        //wysylam wiadomosc 
		if (sendto(s, game->tab, SNDBUFLEN, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
        {
            printf("Proba wyslania blad : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
        }
		else 
			break;
    }
}
//---------------------------------------------------------------------------

void Socket::Close()
{
    closesocket(s);
    WSACleanup();
}