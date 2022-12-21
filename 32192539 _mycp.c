/*
 *mycp.c    : same as cp command
 @author    : Juyeol Yang
 @StudentID : 32192539
 @email     : wnduf212@gmail.com
 @version   : 1.0
 @date      : 2022/11/03 Thu
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){
    int fd1, fd2, read_size, write_size;
    char buf[MAX_BUF];
    struct stat BUF;

    if(argc != 3){
        printf("USAGE: %s file_name copy_file_name\n", argv[0]);
        exit(-1);
    }

    fd1 = open(argv[1], O_RDONLY);
    if(fd1 < 0){
        printf("Can't open %s file with errno %d\n", argv[1], errno);
        exit(-1);
    }
    if(fstat(fd1, &BUF) == -1){
        printf("open errno %d", errno);
        exit(-1);
    }
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, BUF.st_mode);
    if(fd2 < 0){
        printf("Can't open %s file with errno %d\n", argv[2], errno);
        exit(-1);
    }

    while(1){
        read_size = read(fd1, buf, MAX_BUF);
        if(read_size == 0) break;
        write_size = write(fd2, buf, read_size);
    }

    close(fd1); close(fd2);
}