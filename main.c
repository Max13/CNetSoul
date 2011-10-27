////////////////////////////////////////////////////////////////////////
//                               Main.c                               //
////////////////////////////////////////////////////////////////////////
//            Auteur: Adnan RIHAN (Max13) <adnan@rihan.fr>            //
////////////////////////////////////////////////////////////////////////

#include "conf.h"

int main(int argc, char *argv[])
{
	socks_init();

    SOCKET sock;
    HOSTENT *hostinfo;
    SOCKADDR_IN sin = { 0 };
    pthread_t *threadID;

	socks_connect(&sock, hostinfo, &sin);
	socks_authentification(&sock);

	pthread_create(threadID, NULL, recv_waiting, NULL);

	closesocket(sock);
	socks_end();
	system("PAUSE");
	return 0;
}
