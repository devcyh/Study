#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void ErrorHandling(char *message);
#define MAX_PACKET_SIZE  120

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAdr;
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 

	hSocket=socket(PF_INET, SOCK_STREAM, 0);   
	if(hSocket==INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servAdr.sin_port=htons(9000);

	// TCP 연결 요청...
	int ret;
	ret = connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr) );
	if (ret == SOCKET_ERROR) {
		printf("<ERROR> Client. connect() 실행 오류.\n");
		closesocket(hSocket);
		printf("Client> close socket...\n");
		WSACleanup();
		return 0;
	}
	else {
		printf("Client> connection established...\n");
	}
	
	// send/recv...
	int command, flag;
	char data[MAX_PACKET_SIZE];
	int* intp;
	intp = (int *)data;
	flag = 1;
	for (int i = 0; i < MAX_PACKET_SIZE / sizeof(int); i++) {
		intp[i] = i + 501;
	}
	while (flag) {
		printf("Client> try to send(1:start, 0:stop):");
		scanf("%d", &command);
		if (command == 1) {
			// 1. 120 바이트 send
			ret = send(hSocket, data,sizeof(data), 0);
			printf("Client> sent %d bytes...\n", ret);

			// 2. 1 바이트 recv
			ret = recv(hSocket, data, 1, 0 );
			if (ret <= 0) {
				printf("<ERROR> recv 오류.(%d).\n", ret);
			}
			else {
				printf("Client> recv %d 바이트 수신.\n", ret);
			}
		}
		else {
			// stop...
			flag = 0;
		}

	}

	closesocket(hSocket);
	printf("Client> close socket...\n");
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}