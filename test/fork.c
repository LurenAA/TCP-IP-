#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid;

    if((pid = fork()) == -1)
        perror("fork err");
    else if(!pid){
        exit(0);
}
    sleep(1);
    system("ps");

    return 0;
}