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
	SOCKADDR_IN servAdr, servAdr2;
	int servAdrSize;
	servAdrSize = sizeof(servAdr2);
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 

	hSocket = socket(PF_INET, SOCK_DGRAM, 0);  // UDP ���� 
	if(hSocket==INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servAdr.sin_port=htons(9000);

	int ret;
	ret = connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr) ); // connected UDP
	
	
	// 1. send/recv �� ���� ��� �Է¹ް� ������ �����ϰ� ��� ����...
	char msg[MAX_PACKET_SIZE];
	int opndCnt, rcvSum, rcvTotal, result, flag;
	flag = 1;
	while (flag)
	{
		// 1. ����� ���� �ڷ� �Է�....(�ǿ����� ��, �ǿ�����, ������)
		//    - msg ����
		//    - send( msg );
		printf("Client: �ǿ����� �� �Է�: ");
		scanf("%d", &opndCnt);
		msg[0] = (char)opndCnt;
		for (int i = 0; i < opndCnt; i++) {
			printf("- %d ��° �ǿ����� �Է�: ", i+1);
			scanf("%d", &msg[1+i*sizeof(int)]);
		}
		rewind(stdin);
		printf("> �����ڸ� �Է��ϼ���: ");
		scanf("%c", &msg[1+opndCnt*sizeof(int)]);

		// UDP sendto
		//send(hSocket, msg, 2+opndCnt*sizeof(int), 0);
		send(	hSocket, msg, 2 + opndCnt * sizeof(int), 0 );

		// 2. ��� ���� �� ���
		//    - recv( msg );
		//    - ��� ���.
		//ret = recv(hSocket, &msg[rcvSum], rcvTotal - rcvSum, 0);
		ret = recv(	hSocket, (char*)&result, sizeof(result), 0 );
		
		printf("Client> �����κ��� ���ŵ� ��� = %d\n", result);
		
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