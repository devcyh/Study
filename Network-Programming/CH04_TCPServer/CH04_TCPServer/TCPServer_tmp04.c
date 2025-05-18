#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void ErrorHandling(char *message);
#define MAX_PACKET_SIZE  120
int main(void)
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;

	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 
	
	hServSock = socket(PF_INET, SOCK_STREAM, 0);  

	if(hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAdr.sin_port=htons(9000);

	if(bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr))==SOCKET_ERROR)
		ErrorHandling("bind() error");
	
	// Ŭ���̾�Ʈ���� ������ �غ� �Ϸ�...
	listen(hServSock, 3);

	while (1) {
		printf("Server> Ŭ���̾�Ʈ ���� ���� ��� ��.\n");

		clntAdrSize = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		if (hClntSock == -1) {
			printf("<ERROR> accept ���� ����.\n");
		}
		else {
			printf("Server> client(IP:%s, Port:%d) �����.\n",
				inet_ntoa(clntAdr.sin_addr), ntohs(clntAdr.sin_port));
		}

		// recv/send
		int flag, ret;
		flag = 1;
		char data[MAX_PACKET_SIZE];
		int rcvSum, rcvTotal;

		while (flag) {
			// 1. recv from a client (120����Ʈ ���� -> ȭ�� ���.
			// - recv �� ������ ȣ���ؾ� �� �� �ִ�. <- �߿�! ���迡 ����.
			rcvSum = 0;
			rcvTotal = MAX_PACKET_SIZE; // ��ǥ �޴� ������ ũ��
			while (rcvSum < rcvTotal) {
				ret = recv(hClntSock, &data[rcvSum], rcvTotal-rcvSum, 0);
				if (ret <= 0) {
					printf("Server> recv ����(%d).\n", ret);
					flag = 0;
					break;
				}
				else {
					rcvSum += ret;
					printf("Server> recv %d bytes ����.(����: %d bytes)\n", ret, rcvSum);
				}
			}
			int* intp;
			intp = (int*)data;
			if (flag == 1) {
				// ���� ��Ŷ�� ȭ�鿡 ���....
				printf("Server> ���ŵ� ��Ŷ ����:\n");
				for (int i = 0; i < MAX_PACKET_SIZE / sizeof(int); i++) {
					printf("%d ", intp[i]);
				}
				printf("\n");

				// 2. send('A');
				data[0] = 'A';
				send(hClntSock, data, 1, 0);
				printf("Server> sent ack to the client.\n");
			}
		}
		printf("Server> Ŭ���̾�Ʈ�� ���� ����.\n");
		closesocket(hClntSock);
	}

	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}