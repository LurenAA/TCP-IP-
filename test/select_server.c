#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("socket");
    exit(1);
  }

  int opval = 1;
  socklen_t opvalLen = sizeof(opval);
  if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opval, opvalLen)){
    perror("setsockopt error");
    exit(1);
  }
 
  struct sockaddr_in sockAddr, clientSock;
  memset(&sockAddr, 0, sizeof(sockAddr));
  sockAddr.sin_family = AF_INET;
  sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  sockAddr.sin_port = htons(8080);

  if(bind(sockfd, (struct sockaddr*)&sockAddr, (socklen_t)sizeof(sockAddr)) == -1) {
    perror("error bind");
    exit(1);
  }

  if(listen(sockfd, 5) == -1) {
    perror("error listen");
    exit(1);
  }
  int nfds = sockfd, res;
  fd_set reads, tmps;
  FD_ZERO(&reads);
  FD_SET(sockfd, &reads);  
  struct timeval time;

  while(1) {
    tmps = reads;
    time.tv_sec = 5;
    time.tv_usec = 0;

    res = select(nfds + 1, &tmps, 0 ,0, &time);
    if(res == 0) {
      puts("time out\n");
    } else if (res == -1) {
      perror("error in select");
      exit(1);
    } else {
      for (int i = 0; i < nfds + 1; i++) {
        if(FD_ISSET(i, &tmps)) {
          if(i == sockfd) {
            socklen_t socklen = sizeof(clientSock);
            memset(&clientSock, 0, sizeof(clientSock));
            int curSock = accept(sockfd, (struct sockaddr*)&clientSock, &socklen);
            if(curSock == -1) {
              perror("accept error");
              exit(1);
            }
            if(curSock > nfds) {
              nfds = curSock;
            }
            FD_SET(curSock, &reads);
          } else {
            char buf[80];
            int readLen = read(i, buf, 80);
            if(readLen == 0) {
              printf("%d exit \n", i);
              FD_CLR(i, &reads);
              close(i);
            } else {
              write(i, buf, readLen);
            }
          }
        }
      }
    }
  }
  close(sockfd);
}