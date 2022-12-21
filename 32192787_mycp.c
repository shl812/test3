#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char* argv[]){
    int fd, fd1, read_size, write_size;
    char buf[MAX_BUF];
    struct stat sbuf;
    if(argc != 3){
        printf("USAGE : %s input_file_name output_file_name\n", argv[0]);
        exit(-1);
    }
    fd = open(argv[1], O_RDONLY);
    fd1 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0641);
    if(fd == -1 || fd1 == -1){
        printf("ERROR, FILE OPEN FAIL");
        exit(-1);
    }               
    fstat(fd,&sbuf);
    fchmod(fd1,sbuf.st_mode);
    dup2(fd1, STDOUT_FILENO);
    while(1){
        read_size = read(fd, buf, MAX_BUF);
        if(read_size == 0){
            break;
        }
        write_size = write(STDOUT_FILENO, buf, read_size);
    }    
    close(fd); close(fd1);
}