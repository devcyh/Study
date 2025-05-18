
#include <stdio.h>
#include <WinSock2.h>
#define MAX_BUF_SIZE 100
int main(void)
{
	WSADATA		winsockData;
	int			errorNum, errorCode;

	printf("> 클라이언트 실행. \n");

	// 1. 소켓 라이브러리 초기화
	errorNum = WSAStartup( MAKEWORD(2,2), &winsockData );
	if (errorNum == 0) { // 함수 실행 성공..
		printf("> 소켓 초기화 성공.\n");
	}
	else {
		printf("> 소켓 초기화 실패. 오류코드(%d)\n", errorNum);
		return 1;
	}

	// 2. 소켓 생성, param  프로토콜 지정, TCP
	SOCKET clientSocket;
	clientSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
	if (clientSocket == INVALID_SOCKET) {
		errorCode = WSAGetLastError();
		printf("<error> 오류 발생, 코드(%d).\n", errorCode);
	}

	SOCKADDR_IN  serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family			= AF_INET;
	serverAddr.sin_port				= htons(9000);  	
	serverAddr.sin_addr.s_addr		= inet_addr("127.0.0.1");

	// 서버와 연결하기...
	errorNum = connect(clientSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr) );
	if (errorNum == SOCKET_ERROR) {
		errorCode = WSAGetLastError();
		printf("<error> 오류 발생, 코드(%d).\n", errorCode);
	}

	printf("> 클라이언트가 서버와 TCP 연결 되었습니다.\n");

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
			printf("> Half-close 수신. 파일 데이터 수신 완료..\n");
			break;
		}
	}
	printf("> 파일 수신 완료.\n");
	send(clientSocket, "Thank you", sizeof("Thank you"), 0);
	fclose(fp);
	//---E------------------------------------------------------------

	printf("> 클라이언트가 서버와 TCP 연결을 종료합니다.\n");

	// 소켓 종료
	errorNum = closesocket(clientSocket);
	if (errorNum == SOCKET_ERROR) {
		errorCode = WSAGetLastError();
		printf("<error> 오류 발생, 코드(%d).\n", errorCode);
	}

	// 소켓 사용 종료...
	errorNum = WSACleanup();
	if (errorNum == SOCKET_ERROR) {
		errorCode = WSAGetLastError();
		printf("<error> 오류 발생, 코드(%d).\n", errorCode);
	}
}

