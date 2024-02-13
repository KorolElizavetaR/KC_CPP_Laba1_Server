#define PORT 1234

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

int GCD(int a, int b);
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

using namespace std;

#pragma warning(disable: 4996)

void main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0) {
		cout << "Error #2\n";
		return;
	}
	cout << "Client Connected!\n";


	char ach[15] = "", bch[15] = "";
	recv(newConnection, ach, sizeof(ach), 0);
	std::cout << "A received: " << ach << endl;
	recv(newConnection, bch, sizeof(bch), 0);
	std::cout << "B received: " << bch << endl;

	int a = atoi(ach);
	int b = atoi(bch);

	int gcd = GCD(a,b);
	char gcdch[15] = "";
	itoa(gcd, gcdch, 10);
	send(newConnection, gcdch, sizeof(gcdch), 0);

	return;
}



int GCD(int a, int b)
{
	if (a == 0)
		return b;
	return GCD(b % a, a);
}