// 32204309 2022/11/01

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char *argv[]) {
    int fd, fd1, read_size, write_size, access;
    char buf[MAX_BUF];
    struct stat fd_stat;

    if(argc != 3) {
        printf("USAGE : %s input_file_name output_file_name\n", argv[0]);
        exit(-1);
    }
    fd = open(argv[1], O_RDONLY);
    access = fstat(fd, &fd_stat);

    fd1 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, fd_stat.st_mode);

    while(1) {
        read_size = read(fd, buf, MAX_BUF);
        if(read_size == 0)
            break;
        write_size = write(fd1, buf, read_size);
    }

    close(fd);

    return 0;
}