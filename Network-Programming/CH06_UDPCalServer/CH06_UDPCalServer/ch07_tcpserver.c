// ���� ���α׷�.
#include <stdio.h>
#include <WinSock2.h>
#define  MAX_BUF_SIZE  100
int main(void)
{
	WSADATA   winsockData;
	printf("> ���� ���α׷� ����.\n");

	// 1. ���� �ʱ�ȭ...���� ���̺귯���� ����...
	WSAStartup( MAKEWORD(2,2), &winsockData );

	// 2. ������ ���� �ϱ�...
	SOCKET serverSocket;
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN   serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET;
	serverAddr.sin_port			= htons(9000); 
	serverAddr.sin_addr.s_addr	= inet_addr("127.0.0.1");

	// 3. bind() �Լ� ȣ��...
	// - ������ ���� IP, port ����...
	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	// 4. listen() �Լ� ȣ��...
	int backLog = 3; 
	listen(serverSocket, backLog );

	// 5. accept �Լ� ȣ��...
	SOCKET			clientSocket;
	SOCKADDR_IN		clientAddr;
	int				addrLen;
	addrLen = sizeof(clientAddr);

	printf("> accept �Լ��� ȣ���Ͽ� Ŭ���̾�Ʈ ���� ��û�� ����մϴ�.\n");
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &addrLen);

	printf("> Ŭ���̾�Ʈ(IP:%s, Port:%d)�� ����Ǿ����ϴ�.\n",
		inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

	//---S------------------------------------------------------------
	FILE* fp;
	char buf[MAX_BUF_SIZE];
	int  recvCnt, recvedTotalBytes, TargetSize;
	fp = fopen("file_server_win.c", "rb");

	while (1) {
		// �д� ����Ʈ �� : n x count ����Ʈ
		recvCnt = fread((void *)buf, 1, MAX_BUF_SIZE, fp );
		if (recvCnt < MAX_BUF_SIZE) {
			send(clientSocket, buf, recvCnt, 0);
			break;
		} // ������ �κ� ũ�� �ٸ��� �̿��� ����
		send(clientSocket, buf, recvCnt, 0);
	}

	shutdown(clientSocket, SD_SEND); // ��½�Ʈ�� �˴ٿ�

	TargetSize = strlen("Thank you");
	recvedTotalBytes = 0;
	while (recvedTotalBytes < TargetSize) {
		recvCnt = recv(clientSocket, (char*)&buf[recvedTotalBytes],
			TargetSize - recvedTotalBytes, 0);
		recvedTotalBytes += recvCnt;
	}
	buf[recvedTotalBytes] = 0; // string �� �ΰ��ε�
	printf("> client�κ��� ���� �޽��� : %s\n", buf);
	fclose(fp);
	//---E------------------------------------------------------------

	printf("> Ŭ���̾�Ʈ(IP:%s, Port:%d)�� ������ �����մϴ�.\n",
		inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

	// Ŭ���̾�Ʈ ������ ���� ��� ����...
	closesocket(clientSocket);
	
	// ������ ���� ��� ����...
	closesocket(serverSocket);

	// ���� ��� ����..
	WSACleanup();

	return 0;
}



/*
	// recv() �Լ��� ���� ��� tcp client�κ��� ������ ����
	// send(100B), send(100B), send(100B), send(100B), send(100B)
	char Buffer[MAX_BUF_SIZE];
	int  returnValue, stopFlag=0, index=1;

	while (stopFlag == 0) {

		returnValue = recv(clientSocket, Buffer, MAX_BUF_SIZE, 0);

		if (returnValue > 0) // ������ �����͸� ������ ���...
		{
			printf("%d> %d ����Ʈ �����͸� ����.\n", index, returnValue);
			index++;
		}
		else if (returnValue == SOCKET_ERROR) {
			printf("<error> recv() �Լ� ���� �� ���� �߻�, code(%d)\n", WSAGetLastError());
		}
		else if (returnValue == 0) {
			// ���� ���� ����...
			printf("> client�� socket�� ����\n");
			stopFlag = 1;
		}

		//Sleep(1000);
	}
*/