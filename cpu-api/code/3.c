#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int rc = fork();

    if (rc == -1)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        //child process

        int execution = execvp("/bin/ls", "/Users/yooseungjun");
        if (execution == -1)
        {
            fprintf(stderr, "ls execution failed\n");
            exit(1);
        }

        printf("not reachable\n");
    }
    else
    {
        // parent process
        printf("i am parent\n");
    }

    return 0;
}