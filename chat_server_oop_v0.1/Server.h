#pragma once
#include <WS2tcpip.h>
#include <string.h>

#pragma comment(lib,"Ws2_32.lib")
class Server
{
private:
	static SOCKET ClientSocket;
	char name[MAX_PATH];
	SOCKET ListenSocket;

	addrinfo *result, *ptr, hints;
	HANDLE ListenThread;
	
public:
	void createMesage();
	void sendMessage(char* mtext);
	void createThread();
	static DWORD WINAPI Listening(LPVOID lpParam);
	Server(void);
	~Server(void);
};

