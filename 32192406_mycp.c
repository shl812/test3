/*
 * 학과 : 소프트웨어학과
 * 학번 : 32192406
 * 이름 : 심의진
 * 수정 : 2022.11.04.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){
    int fd, fd_copy, read_size;
    char buf[MAX_BUF];
    struct stat stat_buf;
    
    if(argc != 3){
        printf("USAGE : %s file_name copy_name \n", argv[0]);
        exit(-1);
    } // ./mycp file_name copy_name 형식으로 명령어를 작성하지 않았을 경우 출력하는 에러 메시지
    
     if(open(argv[2], O_RDONLY)>0){
        printf("Can't copy file : %s file already exist\n", argv[2]);
        exit(-1);
    } // copy_name이 이미 존재하는 파일명일 경우 출력하는 에러 메시지
    
    fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        printf("Can't open %s file with errno %d\n", argv[1], errno);
        exit(-1);
    } // 파일을 여는데 실패했을 경우 출력하는 에러 메시지
   
    if(stat(argv[1], &stat_buf) == -1){
        printf("Can't load %s stat with errno %d\n", argv[1], errno);
        exit(-1);
    } // file_name의 정보를 얻어오는데 실패했을 경우 출력하는 에러 메시지
    
    stat(argv[1], &stat_buf);
    mode_t permission = stat_buf.st_mode;
    
    fd_copy = open(argv[2], O_WRONLY|O_CREAT|O_EXCL, permission);
    if(fd_copy < 0){
        printf("Can't open %s file with errno %d/n", argv[2], errno);
        exit(-1);
    } // 원본파일을 복사하기 위한 fd_copy를 생성하고
      // fd_copy가 생성한 파일을 여는데 실패했을 경우 출력하는 에러 메시지
    

    while(1){
        read_size = read(fd, buf, MAX_BUF);
        if(read_size == 0)
            break;
        write(fd_copy, buf, read_size);
    } // read()를 통해 읽어들인 값이 없을 경우에만 종료하는 loop, 
      // 읽어들인 값은 fd_copy를 통해 copy_name 파일에 저장된다.
    
    close(fd);
    close(fd_copy);
    
    return 0;
}

/*
 * 아래의 링크를 참고하여 코드를 작성하였음. (stat 함수 관련)
 * https://www.it-note.kr/173
 */