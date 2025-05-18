
#include <stdio.h>
#include <WinSock2.h>
#define MAX_BUF_SIZE 100
int main(void)
{
	WSADATA		winsockData;
	int			errorNum, errorCode;

	printf("> Ŭ���̾�Ʈ ����. \n");

	// 1. ���� ���̺귯�� �ʱ�ȭ
	errorNum = WSAStartup( MAKEWORD(2,2), &winsockData );
	if (errorNum == 0) { // �Լ� ���� ����..
		printf("> ���� �ʱ�ȭ ����.\n");
	}
	else {
		printf("> ���� �ʱ�ȭ ����. �����ڵ�(%d)\n", errorNum);
		return 1;
	}

	// 2. ���� ����, param  �������� ����, TCP
	SOCKET clientSocket;
	clientSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
	if (clientSocket == INVALID_SOCKET) {
		errorCode = WSAGetLastError();
		printf("<error> ���� �߻�, �ڵ�(%d).\n", errorCode);
	}

	SOCKADDR_IN  serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family			= AF_INET;
	serverAddr.sin_port				= htons(9000);  	
	serverAddr.sin_addr.s_addr		= inet_addr("127.0.0.1");

	// ������ �����ϱ�...
	errorNum = connect(clientSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr) );
	if (errorNum == SOCKET_ERROR) {
		errorCode = WSAGetLastError();
		printf("<error> ���� �߻�, �ڵ�(%d).\n", errorCode);
	}

	printf("> Ŭ���̾�Ʈ�� ������ TCP ���� �Ǿ����ϴ�.\n");

	//---S------------------------------------------------------------
	char buf[MAX_BUF_SIZE];
	int  recvCnt;
	FILE* fp;

	fp = fopen("received.dat", "wb");

	while (1) {
		recvCnt = recv(clientSocket, buf, MAX_BUF_SIZE, 0);
		if (recvCnt != 0) {
			fwrite((void *)buf, 1, recvCnt, fp);
		}
		else {
			printf("> Half-close ����. ���� ������ ���� �Ϸ�..\n");
			break;
		}
	}
	printf("> ���� ���� �Ϸ�.\n");
	send(clientSocket, "Thank you", sizeof("Thank you"), 0);
	fclose(fp);
	//---E------------------------------------------------------------

	printf("> Ŭ���̾�Ʈ�� ������ TCP ������ �����մϴ�.\n");

	// ���� ����
	errorNum = closesocket(clientSocket);
	if (errorNum == SOCKET_ERROR) {
		errorCode = WSAGetLastError();
		printf("<error> ���� �߻�, �ڵ�(%d).\n", errorCode);
	}

	// ���� ��� ����...
	errorNum = WSACleanup();
	if (errorNum == SOCKET_ERROR) {
		errorCode = WSAGetLastError();
		printf("<error> ���� �߻�, �ڵ�(%d).\n", errorCode);
	}
}

