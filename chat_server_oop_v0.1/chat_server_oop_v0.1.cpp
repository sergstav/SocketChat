// chat_server_oop_v0.1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Server.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Server s;
	s.createMesage();
	system("pause");
	return 0;
}

