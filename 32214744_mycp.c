/**
 * mycp.c	: copy command program
 * @author	: Seha Tak
 * @studID	: 32214744
 * @email	: 32214744@dankook.ac.kr
 * @version	: 1.0
 * @date	: 2022.11.04
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 64

int main(int argc, char *argv[]) {
    int fd_1, fd_2, read_size, write_size;
    char buf[MAX_BUF];

    if (argc != 3) {    // 에러 처리 : 입력 매개변수가 2개가 아니면
        printf("Error : missing file_name");    // 에러메세지 출력
        exit(-1);
    }
    if(! strcmp(argv[1], argv[2])) {    // 에러 처리 : 복사 대상 파일명과 생성 파일명이 같으면
        printf("Error : same file_names");    // 에러메세지 출력
        exit(-1);
    }
    fd_1 = open(argv[1], O_RDONLY);    // fd_1 : 읽기 전용으로 복사 대상 파일 열기
    fd_2 = open(argv[2],O_RDWR|O_CREAT|O_EXCL); // fd_2 : 읽기 쓰기 가능하도록 파일 생성
    if (fd_1 < 0) {    // 에러 처리 : 파일 읽기 에러 발생 시
        printf("Can't open %s file with errno%d\n", argv[1], errno);    // 에러메세지 출력
        exit(-1);
    }
    if (fd_2 < 0) {    // 에러 처리 : 파일 생성 에러 발생 시
        printf("Can't create %s file with errno%d\n", argv[2], errno);    // 에러메세지 출력
        exit(-1);
    }

    while (1) {
        read_size = read(fd_1, buf, MAX_BUF);    // read_size : 복사 대상 파일 읽기
        if (read_size == 0) {    // 더 이상 읽을 게 없으면
            break;    // while문 빠져나가기
        }
        write_size = write(argv[2], buf, read_size);    // write_size : 복사 대상 파일 내용 터미널에 출력
    }

    close(fd_1);    // 복사 대상 파일 닫기
    close(fd_2);    // 생성 파일 닫기

    return 0;

}