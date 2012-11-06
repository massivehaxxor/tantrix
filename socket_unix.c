#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

static int sockfd;

void connect(char *host, char *port)
{
  struct addrinfo *hints, res;
   
  memset(&hints, 0, sizeof(hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(host, port, &hints, res);
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  connect(sockfd, res->ai_addr, res->ai_addrln);
}

