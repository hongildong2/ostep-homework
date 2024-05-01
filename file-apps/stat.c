#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>


void print_file(struct stat sb, char* name);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        return -1;
    }

    struct stat sb;
    char* path = argv[1];
    stat(path, &sb);

    print_file(sb, path);
    return 0;
}

void print_file(struct stat sb, char* name)
{
    printf("%-10s | %-10s | %-10s | %-10s | %-10s\n", "file_name", "block_size", "file_size", "ref_count", "flag");
    printf("%-10s | %-10d | %-10d | %-10d | %-10d\n", name ,sb.st_blksize, (int) sb.st_size, sb.st_nlink, sb.st_flags);
}