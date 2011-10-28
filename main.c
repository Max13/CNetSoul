////////////////////////////////////////////////////////////////////////
//                               Main.c                               //
////////////////////////////////////////////////////////////////////////
//            Auteur: Adnan RIHAN (Max13) <adnan@rihan.fr>            //
////////////////////////////////////////////////////////////////////////

#include "conf.h"

int main(int argc, char *argv[])
{
	system(CLEAR);
	socks_init();

	SOCKET sock;
	HOSTENT *hostinfo;
	SOCKADDR_IN sin = { 0 };
	pthread_t *threadID;
	S_UINFO u_info;

	printf("NetSoul Username (unix login): ");
	gets(u_info.username);

	printf("Your password (socks): ");
	gets(u_info.password);

	system(CLEAR);

	socks_connect(&sock, hostinfo, &sin);
	socks_authentification(&sock, &u_info);

	pthread_create(threadID, NULL, recv_waiting, NULL);

	closesocket(sock);
	socks_end();
	system("PAUSE");
	return 0;
}
