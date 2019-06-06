#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  fd_set reads,
    tmps;
  FD_ZERO(&reads);
  FD_SET(0, &reads);
  struct timeval timeout;
  int result;

  while(1) {
    tmps = reads;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    result = select(1, &tmps, 0, 0, &timeout);
    if(result == -1) {
      puts("error");
      break;
    } else if (result == 0) {
      puts("time out");
    } else {
      if(FD_ISSET(0, &tmps)) {
        char buf[80];
        int len = read(0, buf, 80);
        buf[len] = 0;
        printf("%s\n", buf);
      }
    }

  }

  return 0;
}