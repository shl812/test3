/**
 * mycp.c  : cp command program 
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
#include <sys/stat.h>

#define MAX_BUF 64

int main(int argc, char *argv[]){   //argv[0] : ./mycp, argv[1] : 복사할 파일 명, argv[2] : 새로운 파일 명
    
    int fd1, fd2, read_size, write_size;
    char buf[MAX_BUF];
    struct stat info;
    mode_t mode;
    int return_stat;

    //명령어 원래파일이름 새로만들파일이름 (ex: ./mycp abc.txt abc2.txt) => argc=3
    if(argc != 3){    
        printf("USAGE : %s file_name\n", argv[0]); 
        exit(-1);
    }

    //원래 파일 열기 (읽기 전용)
    fd1 = open(argv[1], O_RDONLY);
    if(fd1 < 0){
        printf("Can't open %s file with errno %d\n", argv[1], errno);
        exit(-1);
    }

    //새로운 파일 생성하기
    fd2 = open(argv[2], O_RDWR | O_CREAT | O_EXCL);
    if(fd2 < 0){
        printf("Can't Craete %s file with errno %d\n", argv[2], errno);
        exit(-1);
    }

    //원래 파일 읽고 새로운 파일에 쓰기 (MAX_BUF만큼)
    while(1){
        read_size = read(fd1, buf, MAX_BUF);
        if(read_size == 0) break;
        write_size = write(fd2, buf, read_size);

    }
    
    //권한 복사
    return_stat = stat(argv[1], &info);  //복사할 파일의 정보 저장
    if(return_stat < 0){
        printf("Can't Bring Information %s file with errno %d\n", argv[1], errno);
        exit(-1);
    }
    
    mode = info.st_mode; //복사할 파일의 권한 정보 저장

    chmod(argv[2],info.st_mode); //새로운 파일의 권한 변경 CHANGE MODE
    
    close(fd1);
    close(fd2);

    return 0;
}