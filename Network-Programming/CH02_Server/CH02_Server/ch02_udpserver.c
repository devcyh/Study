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
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0) // WSAStartup : ������� �Լ�. �������� �����Լ� �޸𸮿� �÷���. (���� ȣ�� : �����߿� �޸� �Ҵ�)
		ErrorHandling("WSAStartup() error!"); 
	
	servSock=socket(PF_INET, SOCK_DGRAM, 0); // ���� ����. SOCK_DGRAM = udp ����Ѵ� ����
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
	closesocket(servSock); // ���� ����.
	WSACleanup(); // WSAStartup�� �Ҵ�� �޸𸮸� ����� ������ Ȯ�� �� Ǯ����.
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}