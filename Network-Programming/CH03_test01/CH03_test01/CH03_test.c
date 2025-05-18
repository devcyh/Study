// ���� ���α׷�.
#include <stdio.h>
#include <WinSock2.h>
#define  MAX_BUF_SIZE  1000
int main(void)
{
	WSADATA   winsockData;
	
	// 1. ���� �ʱ�ȭ...���� ���̺귯���� ����...
	WSAStartup( MAKEWORD(2,2), &winsockData );
	printf("- winsock ver : 0x%x \n", winsockData.wVersion);
	printf("- winsock hiver : 0x%x \n", winsockData.wHighVersion);
	printf("- winsock des : %s \n", winsockData.szDescription);
	printf("- winsock status : %s \n", winsockData.szSystemStatus);
	
	// 2. ������ ���� �ϱ�...
	SOCKET ListeningSocket; // ������ ����
	ListeningSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN   serverAddr; // IPv4 �϶� ���
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET; // IPv4
	serverAddr.sin_port			= htons(9000);
	serverAddr.sin_addr.s_addr	= INADDR_ANY; // ���� �ٲٰ� �򿣵������ �ٲ��ִ� �Լ� // inet_addr("1.2.3.4"); //inet_addr("127.0.0.1");

	// �ּұ���ü �� ����ϱ�...
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

	printf("Ȯ�� - Port> %d \n", ntohs(serverAddr.sin_port));
	printf("Ȯ�� - IP> 0x%x \n", ntohl(serverAddr.sin_addr.S_un.S_addr));
	printf("Ȯ�� - IP2> %s \n", inet_ntoa(serverAddr.sin_addr));

	// TCP ���� ������ ���� �ּ� �����ϱ�...
	bind(ListeningSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // TCP���� ���� APP�� ���� �ּҸ� �˷���?

	SOCKADDR* bindAddr;
	bindAddr = (SOCKADDR*)&serverAddr;
	printf("- AF : %d\n", bindAddr->sa_family);
	for (int i = 0; i < 14; i++) {
		printf("- [%d] = 0x%x\n", i, bindAddr->sa_data[i]); // f5 ������ �� ��ǻ�� ���μ����� ��Ʋ������ΰ� Ȯ�ΰ���
	}

	// ȣ��Ʈ ����Ʈ ������ ��Ʈ��ũ ����Ʈ ���� ��...
	unsigned long host_addr, net_addr;
	unsigned short host_port, net_port;
	host_addr = 0x01020304;
	host_port = 0x0809;
	net_addr = htonl(host_addr); // ȣ��Ʈ�� ��Ʋ���� ������ Ȯ�� �� ȣ��Ʈ ����Ʈ�� ��Ʋ ������̸� ��Ʈ��ũ ����Ʈ(�� �����)���� �ٲ�
	net_port = htons(host_port);

	printf("HOST> Addr:0x%x, Port:0x%x\n", host_addr, host_port);
	printf("NET> Addr:0x%x, Port:0x%x\n", net_addr, net_port);

	// ������ ���� ��� ����...
	closesocket(ListeningSocket);
	
	// ���� ��� ����..
	WSACleanup();
	return 0;
}