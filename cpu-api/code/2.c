#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main ()
{
    int fd = open("./2_file-out", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1)
    {
        fprintf(stderr, "opening file failed");
        exit(1);
    }

    int rc = fork();

    if (rc == -1)
    {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (rc == 0)
    {
        // child process

        const char* child_message = "i am child process!";
        write(fd, child_message, strlen(child_message));
    } else
    {
        const char* parent_message = "i am parent process!";
        write(fd, parent_message, strlen(parent_message));
    }
    

    return 0;
}