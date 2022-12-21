/* mycp.c  : cp command program  *
 * Stu ID   : 32195083            *
 * Name     : Koo Heechan         *
 * Email    : koogmlcks@gmail.com *
 * Data     : 2022. 10. 31.       */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char* argv[]) {
    int fd1, fd2, read_size, write_size;
    char buf[MAX_BUF];
    struct stat ptr;    // <sys/stat.h> 사용
    stat(argv[1], &ptr); // 권한 복사를 위한 구조체

    if(argc != 3) { // 인자 값의 개수가 다른 경우
        printf("잘못된 인자 값\n");
        exit(-1); // exit()에서 <stdlib.h> 사용
    }
    
    fd1 = open(argv[1], O_RDONLY); // O_RDONLY 에서 <fcntl.h> 사용
    fd2 = open(argv[2], O_CREAT | O_EXCL | O_RDWR, ptr.st_mode); // 파일생성 | 있는 파일 재생성 X | 읽고쓰기, 권한복사
    
    if(fd1 < 0) { // 대상 파일을 찾을 수 없는 경우
        printf("%s 파일 열기 실패\n", argv[1]);
        exit(-1);
    }
    
    if(fd2 == -1) { // 파일이 존재하는 경우
        printf("%s는 이미 존재하는 파일입니다.\n",argv[2]);
        exit(-1);
    } else if(fd2 < 0) {
        printf("%s 파일을 만들 수 없습니다.\n",argv[2]);
        exit(-1);
    }
    
    while(1) {
        read_size = read(fd1, buf, MAX_BUF);
        if(read_size == 0) { // 더 이상 읽을 파일이 없는 경우
            break;
        }
        write_size = write(fd2, buf, read_size);
    }
    
    close(fd1);
    close(fd2);
    
    return 0;
}
