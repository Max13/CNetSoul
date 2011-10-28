////////////////////////////////////////////////////////////////////////
//                               conf.h                               //
////////////////////////////////////////////////////////////////////////
//            Auteur: Adnan RIHAN (Max13) <adnan@rihan.fr>            //
////////////////////////////////////////////////////////////////////////

#ifndef _CONF_H_
# define _CONF_H_


# include <curses.h>
# include <errno.h>
# include <openssl/md5.h>
//# include <openssl/crypto.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define NS_HOSTNAME "ns-server.epita.fr"
# define NS_PORT 4242

# ifdef WIN32
#  include <winsock2.h>
#  define CLEAR "cls"
# elif defined (linux) || defined (__APPLE__)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <unistd.h> /* close */
#  include <netdb.h> /* gethostbyname */
#  define CLEAR "clear"
#  define INVALID_SOCKET -1
#  define SOCKET_ERROR -1
#  define closesocket(s) close(s)
   typedef int SOCKET;
   typedef struct sockaddr_in SOCKADDR_IN;
   typedef struct sockaddr SOCKADDR;
   typedef struct in_addr IN_ADDR;
# else
#  error not defined for this platform
# endif

typedef struct hostent HOSTENT;
typedef struct
{
  char username[8];
  char password[8];
} S_UINFO;

void socks_init(void);
void socks_connect(SOCKET *, HOSTENT *, SOCKADDR_IN *);
void socks_authentification(SOCKET *, S_UINFO *);
void socks_end(void);
void socks_exit(void);
int socks_error(void);

void *recv_waiting(void *);

void clean_str(char *, int);

#endif
