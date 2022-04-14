// 서버 프로그램.
#include <stdio.h>
#include <WinSock2.h>
#define  MAX_BUF_SIZE  1000
int main(void)
{
	WSADATA   winsockData;
	
	// 1. 소켓 초기화...소켓 라이브러리를 연결...
	WSAStartup( MAKEWORD(2,2), &winsockData );
	printf("- winsock ver : 0x%x \n", winsockData.wVersion);
	printf("- winsock hiver : 0x%x \n", winsockData.wHighVersion);
	printf("- winsock des : %s \n", winsockData.szDescription);
	printf("- winsock status : %s \n", winsockData.szSystemStatus);
	
	// 2. 소켓을 생성 하기...
	SOCKET ListeningSocket; // 리스닝 소켓
	ListeningSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN   serverAddr; // IPv4 일때 사용
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET; // IPv4
	serverAddr.sin_port			= htons(9000);
	serverAddr.sin_addr.s_addr	= INADDR_ANY; // 헥사로 바꾸고 빅엔디안으로 바꿔주는 함수 // inet_addr("1.2.3.4"); //inet_addr("127.0.0.1");

	// 주소구조체 값 출력하기...
	printf("INT> 0x%x\n", serverAddr.sin_addr.S_un.S_addr);
	printf("WORD> 0x%x, 0x%x\n",
		serverAddr.sin_addr.S_un.S_un_w.s_w1,
		serverAddr.sin_addr.S_un.S_un_w.s_w2
	);
	printf("BYTE> 0x%x, 0x%x, 0x%x, 0x%x,\n",
		serverAddr.sin_addr.S_un.S_un_b.s_b1,
		serverAddr.sin_addr.S_un.S_un_b.s_b2,
		serverAddr.sin_addr.S_un.S_un_b.s_b3,
		serverAddr.sin_addr.S_un.S_un_b.s_b4
	);

	printf("확인 - Port> %d \n", ntohs(serverAddr.sin_port));
	printf("확인 - IP> 0x%x \n", ntohl(serverAddr.sin_addr.S_un.S_addr));
	printf("확인 - IP2> %s \n", inet_ntoa(serverAddr.sin_addr));

	// TCP 서버 리스닝 소켓 주소 설정하기...
	bind(ListeningSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // TCP한테 서버 APP의 소켓 주소를 알려줌?

	SOCKADDR* bindAddr;
	bindAddr = (SOCKADDR*)&serverAddr;
	printf("- AF : %d\n", bindAddr->sa_family);
	for (int i = 0; i < 14; i++) {
		printf("- [%d] = 0x%x\n", i, bindAddr->sa_data[i]); // f5 눌르면 이 컴퓨터 프로세서는 리틀엔디안인거 확인가능
	}

	// 호스트 바이트 순서와 네트워크 바이트 순서 비교...
	unsigned long host_addr, net_addr;
	unsigned short host_port, net_port;
	host_addr = 0x01020304;
	host_port = 0x0809;
	net_addr = htonl(host_addr); // 호스트가 리틀인지 빅인지 확인 후 호스트 바이트가 리틀 엔디안이면 네트워크 바이트(빅 엔디안)으로 바꿈
	net_port = htons(host_port);

	printf("HOST> Addr:0x%x, Port:0x%x\n", host_addr, host_port);
	printf("NET> Addr:0x%x, Port:0x%x\n", net_addr, net_port);

	// 소켓을 통한 통신 종료...
	closesocket(ListeningSocket);
	
	// 소켓 사용 종료..
	WSACleanup();
	return 0;
}