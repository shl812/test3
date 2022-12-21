/**
mycp.c 	   : cp command program
@author      : Choi Seung Yeon
@email        : stephanie1631@naver.com
@studentID  : 32204601
@major       : computer engineering
@date         : 2022/11/04
**/

//필요한 헤더들 정의
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 4096
#define COPYMODE 0644

//에러 메세지 출력을 위한 메소드
void mistake(char *a, char *b) {
    fprintf(stderr, "Error: %s ", a);
    perror(b);
    exit(1);
}

int main(int argc, char *argv[]) {
    int in_fd;
	int out_fd;
	int n_chars;
	
    char  buf[BUFSIZE];

    if (argc != 3) {
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(1);
    }

    // 파일이 이미 존재하는 경우
    if ((in_fd = open(argv[1], O_RDONLY)) == -1)
        mistake("can't open ", argv[1]);

    // 새로운 파일을 생성하는 경우
    if ((out_fd = creat(argv[2], COPYMODE)) == -1)
        mistake("can't open ", argv[2]);

    // 기존파일을 새로운 파일로 복사하는 경우
    while ((n_chars = read(in_fd, buf, BUFSIZE)) > 0)
        if (write(out_fd, buf, n_chars) != n_chars)
            mistake("Write error to ", argv[2]);

    if (n_chars == -1)
        mistake("Read error from ", argv[1]);
    
    if (close(in_fd) == -1 || close(out_fd) == -1)
        mistake("Error closing files", "");

    return 0;
}

