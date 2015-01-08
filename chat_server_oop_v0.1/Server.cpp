#include "StdAfx.h"
#include "Server.h"
#include <iostream>
#include "Client.h"

using namespace std;

SOCKET Server::ClientSocket = 0;

Server::Server(void)
{
	int iResult;

	WSADATA wsaData;

	iResult = WSAStartup(MAKEWORD(2,2),&wsaData);
	
	ZeroMemory(&hints,sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL,"33445",&hints,&result);
	
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (ListenSocket == INVALID_SOCKET){
		printf("Error in socket():%ld\n",WSAGetLastError());
		free(result);
		WSACleanup();
		return;
	}

	iResult = bind(ListenSocket,result->ai_addr,(int)result->ai_addrlen);
		/**/

	if (listen(ListenSocket,SOMAXCONN) == SOCKET_ERROR){
		printf("Listen failed!",WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return ;
	}

	ClientSocket = accept(ListenSocket,NULL,NULL);
	if (ClientSocket == INVALID_SOCKET){
		printf("Accept failed!",WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return ;
	}
}


Server::~Server(void)
{
}

DWORD WINAPI Server::Listening(LPVOID lpParam)
{
	char recvbuf[512];
	int recvbuflen = 512;
	int iResult = 0;
	
	while (true)
	{
		iResult = recv(ClientSocket,recvbuf,recvbuflen,0);	
		if (iResult > 0) 
		{
			printf("\nPartner -> %s\n", recvbuf);
			cout<<"You ->";
		}
		else
		{
			closesocket(ClientSocket);
			ClientSocket = 0;
			MessageBox(0,L"User is out!",L"Error connect to client",0);
			MessageBox(0,L"Goodbye!",L"close window",0);
			exit(0);
			break;
			
		}
		
	}
	return 0;
	
}

void Server::createThread()
{
	ListenThread = CreateThread(NULL,0,Server::Listening,NULL,0,NULL);
	system("color A0");
	cout << "User onnine"<<'\n';
}

void Server::sendMessage(char * mtext)
{
	send(ClientSocket,mtext,strlen(mtext) + 1,0);
}

void Server::createMesage()
{
	char str[256];

	this->createThread();

	while(true){
		cin.sync();
		
		cout<<"You ->";
		cin.getline(str,256);	
		sendMessage(str);
		
	}
	ExitThread(0);

}
