
#pragma once
#include <WS2tcpip.h>


#pragma comment(lib,"Ws2_32.lib")
class Client
{
private:
	static SOCKET ConnectSocket;
	addrinfo *result, *ptr, hints;
	HANDLE ListenThread;
	
public:
	bool checkIP();										        //Проверка ип-адреса
	void createMessage();										//Создание сообщения
	void sendMessage(char* text);                               //Отправка сообщения
	void createThread();                                        //Создание потока
	static DWORD WINAPI Listening(LPVOID lpParam);
	Client();
	~Client();
};

