#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarmSignalHandler(int signum) {
  printf("signum: %d\n", signum);
}

int main(int argc, char* argv[]) {
  void (*res)(int);
  signal(SIGALRM, alarmSignalHandler);
  alarm(1);
  sleep(10);

  return 0;
}