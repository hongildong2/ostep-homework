#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int x = 100;

    srand(time(NULL));
    int random = rand();    

    int rc =  fork();
    // child process begin
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        //child process
        x = 1;

        long i = 0;
        while (1)
        {
            i++;
            if (i > 1000000000) break;
        }
        printf("x in the child process : %d\n", x);
    }
    else
    {
        // parent process
        x = 2;

        printf("x in the parent process : %d\n", x);
    }

    char* identity = rc == 0? "child" : "parent";
    printf("i am %s process and x value is %d and random value is %d\n", identity, x, random);

    return 0;
}