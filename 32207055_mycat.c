/**
 * mycat.c  : cat command program
 * @student's ID : 32207055  
 * @Author : 구예원
 * @Email : jastu111@naver.com
 * @Version : 1.0
 * @Date : 2022.11.01
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 64

int main(int argc, char *argv[]){    //argv[0] : ./mycat, argv[1] : 파일 명
    
    int fd, read_size, write_size;
    char buf[MAX_BUF];

    //명령어 파일이름 (ex: ./mycat abc.txt) => argc=2
    if(argc != 2){  
        printf("USAGE : %s file_name\n", argv[0]); 
        exit(-1);
    }

    //파일 열기 (읽기 전용)
    fd = open(argv[1], O_RDONLY);
    // 파일 open 실패 시 fd=-1
    if(fd < 0){  
        printf("Can't open %s file with errno %d\n", argv[1], errno);
        exit(-1);
    }

    //파일 읽기 - read_size가 0이 될 때까지 MAX_BUF만큼 계속 읽음
    while(1){
        read_size = read(fd, buf, MAX_BUF);
        if(read_size == 0) break;
        write_size = write(STDOUT_FILENO, buf, read_size);

    }
    
    close(fd);

    return 0;
}