#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int fd = open("README.md", O_RDONLY);
	assert(fd >= 0);
	int fd2 = dup(fd);

    int count = lseek(fd2, 30, SEEK_SET);
    printf("fd offset : %d\n", (int) lseek(fd, 0, SEEK_CUR));
    printf("fd2 offset : %d\n", (int) lseek(fd2, 0, SEEK_CUR));
    close(fd);
    close(fd2);
	return 0;
}