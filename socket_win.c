#include <ws2tcpip.h>
#include <stdio.h>

#define HOST "www.codedumpster.com"

static int sockfd;

static void initWinSock(void)
{
  WSADATA wsa_data;

  if (WSAStartup(MAKEWORD(2, 1), &wsa_data) != 0)
    return;
}

static void t_connect(char *host, char *port)
{
  struct addrinfo hints, *res;

  initWinSock();
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(host, port, &hints, &res) != 0) {
    MessageBox(NULL, "getaddrinfo failed.", "Error", MB_OK);
    return;
  }
  if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
    MessageBox(NULL, "socket failed.", "Error", MB_OK);
    return;
  }
  if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
    MessageBox(NULL, "socket failed.", "Error", MB_OK);
    return;
  }

}

void submit_score(char *score)
{
  char message[512];
  char msgbox_msg[512];
  int s_ret;

  sprintf(message, "GET /tantrix/?%s HTTP/1.0\r\n\r\n", score);

  t_connect(HOST, "80");
  s_ret = send(sockfd, message, strlen(message), 0);
  sprintf(msgbox_msg, "Score sent to server: %s, (%d)", message, s_ret);
  //MessageBox(NULL, msgbox_msg, "Info", MB_OK);
  closesocket(sockfd);
  WSACleanup();
}
