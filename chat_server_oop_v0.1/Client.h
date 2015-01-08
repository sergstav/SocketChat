/*

*/
#pragma once
#include <WS2tcpip.h>
#include "Server.h"

#pragma comment(lib,"Ws2_32.lib")
class Client:public Server
{
private:
	
	addrinfo *result, *ptr, hints;
	HANDLE ListenThread;

public:
	bool checkIP();										        //
	void createMessage();										//
	void sendMessage(char* text);                               //
	void createThread();                                        //
	static DWORD WINAPI Listening(LPVOID lpParam);
	Client();
	~Client();
};

