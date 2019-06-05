#include <stdio.h>
#include <stdlib.h>

void a() {
  printf("abc\n");
}

int main() 
{
  for(int i = 0; i < 5; i++) {
    if(atexit(a)) {
      perror("atexit");
      exit(1);
    }
  }
  
  return 0;
}