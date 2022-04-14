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

	hSocket=socket(PF_INET, SOCK_DGRAM, 0); // UDP 전송
	if(hSocket==INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servAdr.sin_port=htons(9000);

	int ret;
	// ret = connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr) );

	
	// 1. send/recv 를 통해 계산 입력받고 서버로 전달하고 결과 수령...
	char msg[MAX_PACKET_SIZE];
	int opndCnt, rcvSum, rcvTotal, result, flag;
	flag = 1;
	while (flag)
	{
		// 1. 사용자 연산 자료 입력....(피연산자 수, 피연산자, 연산자)
		//    - msg 구성
		//    - send( msg );
		printf("Client: 피연산자 수 입력: ");
		scanf("%d", &opndCnt);
		msg[0] = (char)opndCnt;
		for (int i = 0; i < opndCnt; i++) {
			printf("- %d 번째 피연산자 입력: ", i+1);
			scanf("%d", &msg[1+i*sizeof(int)]);
		}
		rewind(stdin);
		printf("> 연산자를 입력하세요: ");
		scanf("%c", &msg[1+opndCnt*sizeof(int)]);

		// UDP sendto
		//send(hSocket, msg, 2+opndCnt*sizeof(int), 0);
		sendto( hSocket, msg, 2 + opndCnt * sizeof(int), 0,
			(SOCKADDR*)&servAdr, sizeof(servAdr) );

		// 2. 결과 수신 및 출력
		//    - recv( msg );
		//    - 결과 출력.
		// ret = recv(hSocket, &msg[rcvSum], rcvTotal - rcvSum, 0);
		ret = recvfrom( hSocket, (char*)&result, sizeof(result), 0,
			(SOCKADDR*)&servAdr2, &servAdrSize );

			printf("Client> 서버로부터 수신된 결과 = %d\n", result);
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