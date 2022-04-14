#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 300
void ErrorHandling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET servSock;
	char message[BUF_SIZE];
	int strLen;
	int clntAdrSz;
	
	SOCKADDR_IN servAdr, clntAdr;
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0) // WSAStartup : 윈도우용 함수. 동적으로 소켓함수 메모리에 올려줌. (동적 호출 : 실행중에 메모리 할당)
		ErrorHandling("WSAStartup() error!"); 
	
	servSock=socket(PF_INET, SOCK_DGRAM, 0); // 소켓 생성. SOCK_DGRAM = udp 사용한다 지정
	if(servSock==INVALID_SOCKET)
		ErrorHandling("UDP socket creation error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAdr.sin_port=htons(atoi(argv[1]));
	
	if(bind(servSock, (SOCKADDR*)&servAdr, sizeof(servAdr))==SOCKET_ERROR)
		ErrorHandling("bind() error");
	
	while(1) 
	{
		clntAdrSz=sizeof(clntAdr);
		strLen=recvfrom(servSock, message, BUF_SIZE, 0, 
								(SOCKADDR*)&clntAdr, &clntAdrSz);
		message[strLen] = '\0';
		printf("message from client : %s \n", message);
		sendto(servSock, message, strLen, 0, 
								(SOCKADDR*)&clntAdr, sizeof(clntAdr));
	}	
	closesocket(servSock); // 소켓 해제.
	WSACleanup(); // WSAStartup때 할당된 메모리를 사용이 없는지 확인 후 풀어줌.
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}