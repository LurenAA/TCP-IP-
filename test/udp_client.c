#ifdef __cplusplus
  extern "C"
  {
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv, char** argc) {
  if(argv != 3) {
    printf("error in argv\n");
    exit(1);
  }
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock == -1) {
    perror("socket error\n");
    exit(1);
  } 
  
  struct sockaddr_in host, clientAddr;
  memset(&host, 0, sizeof(host));
  memset(&clientAddr, 0, sizeof(clientAddr));
  host.sin_family = AF_INET;
  host.sin_port = (in_port_t)htons(atoi(argc[2]));
  if(!inet_aton(argc[1], &host.sin_addr)) {
    perror("error in inet_aton");
    exit(1);
  }

  socklen_t server_addrlen = (socklen_t)sizeof(host),
    clientAddr_len;
  // if(bind(sock,(struct sockaddr *)&host, server_addrlen) == -1){
  //   perror("error in bind");
  //   exit(1);
  // }

  ssize_t readLen = 0;
  char buf[80]; 
  memset(buf, 0, 80);
  while(1) {
    fgets(buf, 80, stdin);
    printf("input:\n");
    sendto(sock, buf, sizeof(buf) ,0, (const struct sockaddr *)&host, server_addrlen);
    readLen = recvfrom(sock, buf, 80, 0, (struct sockaddr *)&host, &server_addrlen);
    buf[readLen] = 0;
    printf("receive:%s\n", buf);
    memset(buf, 0 ,80);
  }

  close(sock);
  return 0;
}

#ifdef __cplusplus
  }
#endif