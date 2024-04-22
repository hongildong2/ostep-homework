#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define PAGESIZE (4096)
#define NUMPAGES (40)

int main()
{
    const int JUMP = PAGESIZE / sizeof(int);
    const int ARRSIZE = NUMPAGES * JUMP;
    int a[ARRSIZE];
    struct timeval start, end;
    for (int i = 0; i < NUMPAGES * JUMP; i += JUMP) {
        gettimeofday(&start, NULL);
        a[i] += 1;
        gettimeofday(&end, NULL);

        printf("%d passed in a loop\n", end.tv_usec - start.tv_usec);
    }

    return 0;
}