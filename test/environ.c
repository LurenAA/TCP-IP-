#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  // printf("%s\n", environ[1]);   //can`t access environ
  if(putenv((char*)"PWDs=1234")) {
    perror("putenv");
    exit(1);
  }
  printf("%s\n", getenv("PWDs"));

  return 0;
}