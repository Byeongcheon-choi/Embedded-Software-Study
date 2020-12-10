#include <WinSock2.h>
#include <stdio.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

#defind Port xxx
#define Domain xxx
#define Buff xxx


int main() {
	WSADATA wsd;
	struct hostent* Host;
	SOCKADDR_IN addr;
	char data[Buff];

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("Fail to get the Internet address\n");
		WSACleanup;
		system("pause\n");
		return 1;
	}

	Host = gethostbyname("%s\n", Domain);
	if (Host == Null) {
		printf("Not found Domain address\n");
		return;
	}

	printf("Host name : %s\n", Host->h_name);
	printf("Host IP list : %s\n", Host->h_addr_list);

	SOCKET Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
	if (Sock == INVALID_SOCKET) {
		printf("Socket error \n");
		system("pause \n");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(*(struct in_addr*)*myent->h_addr_list));

	printf("%s %d\n", inet_ntoa(*(struct in_addr*)*myent->h_addr_list), PORT);
	printf("%s\n", GET_MSG);

	if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("fail to Final connect\n");
		closesocket(s);
		return 1;
	}
	
	
	ZeroMemory(data, Buff);
	recv(Sock, data, Buff, 0);

	printf("Recieve result : %s \n", data);

	send(Sock, Message, sizeof(Message), 0);

	closesocket(Sock);
	WSACleanup;
	system("pause");
	return 0;

}
