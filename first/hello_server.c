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

int main(int argv, const char** argc) {
  if(argv <= 1) {
    printf("arg error ");
    exit(1);
  }
  int sock_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP),
    sock_client;
  if(sock_server == -1) {
    perror("socket error");
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
    clientAddr_len = (socklen_t)sizeof(clientAddr);
  if(bind(sock_server,(struct sockaddr *)&host, server_addrlen) == -1){
    perror("error in bind");
    exit(1);
  }

  if(listen(sock_server, 5) == -1) {
    perror("error in listen");
    exit(1);
  }

  while(1) {
    sock_client = accept(sock_server, (struct sockaddr *)&clientAddr, &clientAddr_len);
    if(sock_client == -1) {
      perror("accpet error");
      exit(1);
    }
    int len;
    len = write(sock_client, "abc\n", 4);
    close(sock_client);
  } 
  close(sock_server);
  return 0;
}

#ifdef __cplusplus
  }
#endif