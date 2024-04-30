#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./connection.h"

int sockfd;
struct sockaddr_in serv_addr;
struct hostent *server;

void error(const char *msg) {
  perror(msg);
  exit(0);
}

int start_connection(int portno) {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }
  server = gethostbyname("localhost");
  if (server == NULL) {
    error("ERROR, no such host");
  }
  memset((char *)&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  memmove((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR connecting");
  }
  return 1;
}

int write_to_port(char *buffer, int len) {
  int n = write(sockfd, buffer, len);
  if (n < 0) {
    error("ERROR writing to socket");
    return 0;
  }

  return 1;
}

int end_connection(void) {
  close(sockfd);
  return 0;
}