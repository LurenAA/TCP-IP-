#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void sigHandler(int );

int main(int argc, char *argv[])
{
  struct sigaction act;
  sigemptyset(&act.sa_mask);
  act.sa_handler = sigHandler;
  act.sa_flags = 0;
  if(sigaction(SIGCHLD, &act, 0) == -1) {
    perror("sigaction");
    exit(1);
  }
  
  if(fork()) {
    sleep(30);
  } else {
    printf("child end\n");
    exit(3);
  }

  return 0;
}

void sigHandler(int signum) {
  int statu;
  pid_t id = waitpid(-1, &statu, WNOHANG);
  if( WIFEXITED(statu)) {
    printf("id:%d,signum:%d, statu:%d\n",id, signum, WEXITSTATUS(statu));
  }
}