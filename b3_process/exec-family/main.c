#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{    
    printf("Run command <ls -l> after 2 seconds\n");
    sleep(2);
    execl("/bin/ls", "ls", "-l", NULL);

    return 0;   
}
