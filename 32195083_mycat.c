/* mycat.c  : cat command program  *
 * Stu ID   : 32195083            *
 * Name     : Koo Heechan         *
 * Email    : koogmlcks@gmail.com *
 * Data     : 2022. 10. 31.       */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_BUF 64

int main(int argc, char* argv[]) {
    int fd, read_size, write_size;
    char buf[MAX_BUF];
    
    if (argc != 2) {
        printf("잘못된 인자 값\n");
        exit(-1);
    }
    
    fd = open(argv[1], O_RDONLY); // O_RDONLY에서 <fcntl.h> 사용
    
    if (fd < 0) {
        printf("%s 파일 열기 실패\n", argv[1]);
        exit(-1);
    }
    
    while(1) {
        read_size = read(fd, buf, MAX_BUF);
        if (read_size == 0) {
            break;
        }
        write_size = write(STDOUT_FILENO, buf, read_size);  // <unistd.h> 사용해서 STDOUT_FILENO, 그 대신 2 가능
    }
    close(fd);
    return 0;
}

