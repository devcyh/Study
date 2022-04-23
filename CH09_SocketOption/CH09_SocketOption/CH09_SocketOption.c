#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main()
{
	WSADATA wsa;
	SOCKET sock01, sock02;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// Option: SO_TYPE : TCP/UDP type
	sock01 = socket(PF_INET, SOCK_STREAM, 0); // TCP socket 持失.
	sock02 = socket(PF_INET, SOCK_DGRAM, 0); // UDP socket 持失.

	int sock_type, opt_len;
	opt_len = sizeof(sock_type);
	getsockopt(sock01, SOL_SOCKET, SO_TYPE, (char*) & sock_type, &opt_len);
	printf("> Socket type: %d\n", sock_type);

	getsockopt(sock02, SOL_SOCKET, SO_TYPE, (char*)&sock_type, &opt_len);
	printf("> Socket type: %d\n", sock_type);

	closesocket(sock01);
	closesocket(sock02);
	WSACleanup();
	return 0;
}