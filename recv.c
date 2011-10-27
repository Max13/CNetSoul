////////////////////////////////////////////////////////////////////////
//                               recv.c                               //
////////////////////////////////////////////////////////////////////////
//            Auteur: Adnan RIHAN (Max13) <adnan@rihan.fr>            //
////////////////////////////////////////////////////////////////////////

#include "conf.h"

void *recv_waiting(void *sock_ref)
{
	char buffer[2048];
	fd_set rdfs;
	int retFS;
	int n;
	/*
	SOCKET sock = *(SOCKET *) sock_ref;

	do {
		FD_ZERO(&rdfs);
		FD_SET(sock, &rdfs);

		retFS = select(sock, &rdfs, NULL, NULL, NULL);
		if (retFS < 0)
		{
			printf("Disconnected ? - %d\n", retFS);
			socks_exit();
		}
		else if(FD_ISSET(sock, &rdfs))
		{
            n = recv(sock, buffer, 2048, 0);
			if (n <= 0)
				printf("Error on recv: %d - %d\n", n, socks_error());
   			else
				puts(buffer);
		}
	} while (1);
	*/
	puts("TOTO");
}
