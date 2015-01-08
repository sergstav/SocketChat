// chat_client_oop_v0.1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Client.h"
#include <Windows.h>
#include <iostream>


int _tmain(int argc, _TCHAR* argv[], HINSTANCE appInst)
{
	

	Client client;
	if (client.checkIP())
	{
	client.createMessage();
	}
	

	system("pause");
	
	return 0;
}

