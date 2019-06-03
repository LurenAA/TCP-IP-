#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define NI_MAXHOST 1025
#define NI_MAXSERV 32

int main(int argv, const char **argc)
{
  const char node[] = "www.baidu.com";
  const char service[] = "https";
  struct addrinfo hints, *result;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0; /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  int s = getaddrinfo(node, service, &hints, &result);
  if (s != 0)
  {
    printf("123\n");
    exit(EXIT_FAILURE);
  }

  char host[NI_MAXHOST],
    server[NI_MAXSERV];
  memset(host, NI_MAXHOST, 0);
  memset(server, NI_MAXSERV, 0);
  while(result->ai_next)
   result = result->ai_next;
  int ss;
  if ((ss = getnameinfo(result->ai_addr, result->ai_addrlen, host,NI_MAXHOST ,server,NI_MAXSERV, NI_NAMEREQD)) != 0) {
    printf("host:%s\n,server:%s\n,error:%d\n", host, server,ss);
    perror(gai_strerror(ss));
    exit(EXIT_FAILURE);
  }

  printf("host:%s\n,server:%s\n", host, server);

  freeaddrinfo(result);
  return 0;
}