#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

int main()
{
    struct timeval start;
    struct timeval end;

    int i = 0;
    while (i++ < 10)
    {
        gettimeofday(&start, NULL);
        int child = fork();
        gettimeofday(&end, NULL);

        printf("%d consumed for fork() call\n", end.tv_usec - start.tv_usec);
    }
}