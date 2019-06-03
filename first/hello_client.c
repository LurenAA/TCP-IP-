#ifdef __cplusplus
  extern "C" {
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argv, const char** argc) {
  if(argv != 3) {
    printf("error in argv\n");
    exit(1);
  }
  int clientSock = socket(AF_INET, SOCK_STREAM, 0);
  if(clientSock == -1) {
    perror("error in socket\n");
    exit(1);
  }
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = (in_port_t)htons(atoi(argc[2]));
  serverAddr.sin_addr.s_addr = inet_addr(argc[1]);

  socklen_t serverAddrSize = (socklen_t)sizeof(serverAddr);
  if(connect(clientSock, (const struct sockaddr*)&serverAddr, serverAddrSize) == -1) {
    perror("error in connect");
    exit(1);
  }

  ssize_t readLen = 0;
  size_t curIndex = 0;
  char buf[80];
  while(readLen = read(clientSock, &buf[curIndex], 1)) {
    curIndex += readLen;
  }
  
  buf[curIndex] = '\0';
  printf("%s\n", buf);
  close(clientSock);
  return 0;
} 

#ifdef __cplusplus
  }
#endif