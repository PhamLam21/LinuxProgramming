#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

#define LOG     0x01
#define log(...) {  \
    do {    \
        if ((LOG)) { \
            printf("\n[%s:%s:%d] ==>> ", __FILE__, __func__, __LINE__); \
            printf(__VA_ARGS__); \
            printf("\n"); \
        } \
    } while (0); \
} // Logging

int main(int argc, char const *argv[])
{
    struct stat sb;

    if (argc != 2) {
        log("Usage: ./file-infor /path/to/file");
        exit(EXIT_FAILURE);
    }

    if (-1 == lstat(argv[1], &sb)) {
        log("lstat");
        exit(EXIT_FAILURE);
    }

    printf("File Type: ");
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:   printf("block device\n");       break;
        case S_IFCHR:   printf("character device\n");   break;
        case S_IFDIR:   printf("directory\n");          break;
        case S_IFIFO:   printf("FIFO/pipe\n");          break;
        case S_IFLNK:   printf("symlink\n");            break;
        case S_IFREG:   printf("regular file\n");       break;
        case S_IFSOCK:  printf("socket\n");             break;
        default:        printf("unknown?\n");
    }
    
    printf("\nI-node number: %ju, sizeof(uintmax_t): %jd\n\n", (uintmax_t)sb.st_ino, sizeof(uintmax_t));
    printf("File size: %jd bytes\n\n", (intmax_t)sb.st_size);

    printf("Last status change:     %s\n", ctime(&sb.st_ctim.tv_sec));
    printf("Last file access:       %s\n", ctime(&sb.st_atim.tv_sec));
    printf("Last file modification: %s\n", ctime(&sb.st_mtim.tv_sec));

    
    return 0;
}