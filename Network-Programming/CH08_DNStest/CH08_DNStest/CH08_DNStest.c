#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main()
{
	WSADATA wsa;
	char dname[50];
	struct hostent* host;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	while (1) {
		// 1. domain name �Է� : www.tukorea.ac.kr
		printf("> ������ �̸��� �Է��Ͻÿ�(q:������):");
		scanf("%s", dname);
		printf("- domain name: %s\n", dname);
		if ( !strcmp(dname, "q") ) {
			printf("> ���α׷� ���� ����.\n");
			break;
		}

		// 2. hostent = gethostbyname(dname)
		host = gethostbyname( dname );
		if ( !host ) {
			printf("<ERROR> gethostbyname ���� ����.\n");
		}
		else {
			// 3. hostent ����ü ���� ���...
			printf("- official domain name: %s\n", host->h_name);
			for (int i = 0; host->h_aliases[i]; i++) {
				printf("- aliases[%d] = %s\n", i+1, host->h_aliases[i]);
			}
			// AF_INET:IPv4, AF_INET6:IPv6
			printf("- address type: %s\n",
				( host->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6" )
				);
			for (int i = 0; host->h_addr_list[i]; i++) {
				printf("- IP addresses[%d] = %s\n", i+1,
					inet_ntoa( *((struct in_addr*) host->h_addr_list[i]) )
					);
			}
		}
	}

	WSACleanup();
	return 0;
}