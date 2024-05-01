#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void print_file(struct stat sb, char* name);
void print_directory(DIR* dirp, char* cur_path);

int main(int argc, char* argv[])
{
    char path_buff[1024];
    if (argc == 1) {
        getcwd(path_buff, sizeof(path_buff));
    } else if (argc == 2) {
        strcpy(path_buff, argv[1]);
    } else {
        return -1;
    }

    
    DIR* dirp = opendir(path_buff);
    if (dirp == 0) {
        return -1;
    }

    print_directory(dirp, path_buff);

    
    return 0;
}

void print_directory(DIR* dirp, char* cur_path)
{
    char file_buff[2048];
    char path_buff[1024];
    struct stat sb;
    struct dirent* s = readdir(dirp);
    while (s != 0) {
        sprintf(file_buff, "%s/%s",cur_path, s->d_name);
        stat(file_buff, &sb);
        print_file(sb, s->d_name);
        if(S_ISDIR(sb.st_mode) && strcmp(s->d_name, ".") != 0 && strcmp(s->d_name, "..") != 0) {
            puts(" GOING TO CHILD!");
            DIR* child = opendir(file_buff);
            print_directory(child, file_buff);
            puts(" OUT OF CHILD!");
        }
        
        s = readdir(dirp);
    }
}

void print_file(struct stat sb, char* name)
{
    printf("%-10s | %-10s | %-10s | %-10s | %-10s\n", "file_name", "block_size", "file_size", "ref_count", "flag");
    printf("%-10s | %-10d | %-10d | %-10d | %-10d\n", name ,sb.st_blksize, (int) sb.st_size, sb.st_nlink, sb.st_flags);
}