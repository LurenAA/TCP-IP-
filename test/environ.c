#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  // printf("%s\n", environ[1]);   //can`t access environ
  printf("%s\n", getenv("PWD"));

  return 0;
}