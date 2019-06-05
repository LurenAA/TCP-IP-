#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
  // char buf[10];
  // memset(buf, 0 , 10);
  // setbuf(stdout, buf);
  printf("1");
  // fflush(stdout);
  // exit(0); //fflush
  _Exit(0); // no fflush

  return 0;
}