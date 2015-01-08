#include "StdAfx.h"
#include "Client.h"
#include <iostream>


using namespace std;

SOCKET Client::ConnectSocket = 0;

Client::Client()
{
	WSADATA wsaData;

	int iResult;

	iResult = WSAStartup(MAKEWORD(2,2),&wsaData);

	ZeroMemory(&hints,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL,"33445",&hints,&result);

	ptr=result;

	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
    ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Connection Error!",WSAGetLastError());
		free(result);
		WSACleanup();
		return;
	}
				
}

bool Client::checkIP()
{
	int iResult;

	char astr[16];

	sockaddr_in sinfo;

	sinfo.sin_family = AF_INET;
	sinfo.sin_port = htons(33445);
	

	cin.sync();
	cout << "Enter server ip please -> ";
	cin.getline(astr, 16);	

	 
	sinfo.sin_addr.S_un.S_addr = inet_addr(astr);

	iResult = connect(ConnectSocket, (sockaddr*)&sinfo, sizeof(sinfo));

	if (iResult == SOCKET_ERROR) 
	{
		printf("Cannot connect to server!\n",WSAGetLastError());
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		return false;
	}		

	return true;
}

DWORD WINAPI Client::Listening(LPVOID lpParam)
{
	char recvbuf[512];
	int recvbuflen = 512;
	int iResult = 0;

	while (true)
	{
		iResult = recv(ConnectSocket,recvbuf,recvbuflen,0);	
		if (iResult > 0) 
		{
			printf("\nPartner -> %s\n", recvbuf);
			cout<<"You ->";
		}
		else
		{
			closesocket(ConnectSocket);
			ConnectSocket= 0;
			MessageBox(0,L"Server was shutdown!",L"Error connect to server",MB_ICONINFORMATION);
			MessageBox(0,L"Goodbye!",L"close window",0);
			exit(0);
			break;
			
		}
		
	}
	
	return 0;
}

void Client::sendMessage(char* text)
{
	send(ConnectSocket,text,strlen(text)+1,0);
}

void Client::createMessage()
{
	char str[256];
	this->createThread();
	while (true){	
		cout<<"You ->";
		cin.getline(str,256);	
		sendMessage(str);
	}	
}

void Client::createThread()
{
	ListenThread = CreateThread(NULL,0,Client::Listening,NULL,0,NULL);
}

Client::~Client(void)
{
}
