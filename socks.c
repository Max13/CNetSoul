//////////////////////////////////////////////////////////////////////////
//                                socks.c                               //
//////////////////////////////////////////////////////////////////////////
//             Auteur: Adnan RIHAN (Max13) <adnan@rihan.fr>             //
//////////////////////////////////////////////////////////////////////////

#include "conf.h"

void socks_init(void)
{
	#ifdef WIN32
	WSADATA wsa;
	int err;
	
	err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (err < 0)
	{
		puts("WSAStartup Failed...");
		exit(EXIT_FAILURE);
	}
	#endif
}

void socks_connect(SOCKET *sock, HOSTENT *hostinfo, SOCKADDR_IN *sin)
{
	puts("Connexion...");
	*sock = socket(AF_INET, SOCK_STREAM, 0);
	if(*sock == INVALID_SOCKET)
	{
		puts("socket()");
		exit(socks_error());
	}

	hostinfo = gethostbyname(NS_HOSTNAME);
	if (hostinfo == NULL)
	{
		fprintf(stderr, "Unknown host %s.\n", NS_HOSTNAME);
		exit(socks_error());
	}
	sin->sin_addr = *(IN_ADDR *)hostinfo->h_addr;
	sin->sin_port = htons(NS_PORT);
	sin->sin_family = AF_INET;
	if(connect(*sock,(SOCKADDR *) sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		puts("connect()");
		exit(socks_error());
	}
	puts("You are connected !");
}

void socks_authentification(SOCKET *sock, S_UINFO *u_info)
{
	const int bufferSize = 100;
	char recvBuffer[bufferSize];
	char authBuffer[bufferSize];
	MD5_CTX *md5_ctx;
	unsigned char *md5Buffer;
	unsigned char readableMd5Buffer[(MD5_DIGEST_LENGTH * 2 + 1)];
	int n;

	unsigned char recvMd5[32 + 1];
	unsigned short client_port;
	unsigned char client_host[15 + 1];

	clean_str(recvBuffer, bufferSize);
	n = recv(*sock, recvBuffer, bufferSize, 0);
	if (n <= 0)
	{
		printf("Hello from Server error: %d - %d\n", n, socks_error());
		socks_exit();
	}
	puts(recvBuffer);
	sscanf(recvBuffer, "%*s %*u %s %s %hu", recvMd5, client_host, &client_port);

	clean_str(authBuffer, bufferSize);
	strcpy(authBuffer, "auth_ag ext_user none none\n");
	send(*sock, authBuffer, strlen(authBuffer), 0);

	clean_str(recvBuffer, bufferSize);
	n = recv(*sock, recvBuffer, bufferSize, 0);
	if (n <= 0 || strcmp(recvBuffer, "rep 002 -- cmd end\n") != 0)
	{
		printf("Auth Request error: %s // %d\n", recvBuffer, n);
		socks_exit();
	}

	clean_str(recvBuffer, bufferSize);
	sprintf(recvBuffer, "%s-%s/%hu%s", recvMd5, client_host, client_port, u_info->password);

	puts(recvBuffer);
	puts("Recv Put");
	MD5_Init(md5_ctx);
	puts("INIT MD5");
	MD5_Update(md5_ctx, recvBuffer, strlen(recvBuffer));
	puts("UPDATE_MD5");
	MD5_Final(md5Buffer, md5_ctx);
	puts("MD5_Final");
	//md5Buffer = MD5(recvBuffer, strlen(recvBuffer), NULL);

	clean_str(readableMd5Buffer, (MD5_DIGEST_LENGTH * 2 + 1));
	for (n = 0; n < MD5_DIGEST_LENGTH; n++)
		sprintf(&readableMd5Buffer[0 + (2 * n)], "%02x", md5Buffer[n]);
	readableMd5Buffer[(MD5_DIGEST_LENGTH * 2 + 1)] = '\0';

	puts(recvBuffer);

	clean_str(authBuffer, bufferSize);
	sprintf(authBuffer, "ext_user_log %s %s none test\n", u_info->password, readableMd5Buffer);
	puts(authBuffer);
	send(*sock, authBuffer, strlen(authBuffer), 0);

	clean_str(recvBuffer, bufferSize);
	n = recv(*sock, recvBuffer, bufferSize, 0);
	if (n <= 0 || strcmp(recvBuffer, "rep 002 -- cmd end\n") != 0)
	{
		printf("Authentification error: %s // %d\n", recvBuffer, n);
		socks_exit();
	}
	puts("It's ok. You can proceed your commands");
}

void socks_exit(void)
{
	char c;

	printf("Error: %d\n", socks_error());
	getchar();
	exit(socks_error());
}

void socks_end(void)
{
    #ifdef WIN32
	WSACleanup();
	#endif
}

int socks_error(void)
{
	#ifdef WIN32
	return WSAGetLastError();
	#elif defined (linux)
	return errno;
	#endif
}

/*
static char *socks_error_message(void)
{
	#ifdef WIN32
	return FormatMessage();
	#elif defined (linux)
	return errno();
	#endif
}
*/
