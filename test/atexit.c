#include <stdio.h>
#include <stdlib.h>

void b()
{
  printf("123\n");
  _Exit(0); // man exit description
}

void a()
{
  printf("abc\n");
  if (atexit(b))
  {
    perror("atexit");
    exit(1);
  }
}

int main()
{
  if (atexit(a))
  {
    perror("atexit");
    exit(1);
  }
  if (atexit(b))
  {
    perror("atexit");
    exit(1);
  }
  if (atexit(b))
  {
    perror("atexit");
    exit(1);
  }

  _Exit(1); // do not call any functions registered with atexit or on_exit
  return 0;
}