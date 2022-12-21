/**
 * mycp.c       : cp command program
 * @author      : Kangho Lim
 * @email       : 32173672@dankook.ac.kr
 * @version     : 1.0
 * @date        : 2022. 11. 04 
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char* argv[]) {
    int fd1, fd2, read_size, write_size;     // file descriptor 1, file descriptor 2, read_size, write_size
    int attribute;      // file의 permission
    char buf[MAX_BUF];      // buf[64]
    struct stat st;    // file의 정보를 저장하는 stat 구조체

    if (argc != 3) {    // 프로그램 실행 시 인자로 2개 file의 이름이 전달되지 않았을 경우
       printf("USAGE: %s source_file destination_file\n", argv[0]);     // 이 프로그램(mycp.c)의 사용 방법 출력  
       exit(-1);
    }
    stat(argv[1], &st);     // argv[1] file의 정보를 stat 구조체 st 에 저장

    attribute = st.st_mode;     // st의 permission을 저장
    
    fd1 = open(argv[1], O_RDONLY);   // argv[1] file을 O_RDONLY flag로 열고 fd1으로 저장
    if (fd1 < 0) {   // file open을 실패하면
        printf("Can't open %s file with errno\n", argv[1], errno);     // error number와 함께 에러 메세지 출력
        exit(-1);
    }

    fd2 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, attribute);  // argv[2] file을 O_RDWR(읽기, 쓰기), O_CREAT(생성), O_EXCL(O_CREAT flag와 함께 사용하여 이미 파일이 생성된 경우, 다시 생성하지 않고 오류 메세지 출력) flag로 열고, attribute에 담긴 permission으로 접근 권한을 설정하여 fd2에 저장
    if (fd2 < 0) {   // file open을 실패하면
        printf("Can not create %s file with errno %d\n", argv[2], errno);  // error number와 함께 에러 메세지 출력
        exit(-1);
    }
    // if (fd2 == -1) {    // file이 이미 존재하여 open을 실패하면
    //     printf("Can't create %s file with errno %d\n", argv[2], errno);  // 에러 메세지 출력
    //     exit(-1);
    // } else if (fd2 < 0) {   // 그 외의 이유로 file open을 실패하면
    //     printf("Can not create %s file with errno %d\n", argv[2], errno);  // 에러 메세지 출력
    //     exit(-1);
    // }

    while (1) {     // file의 내용을 전부 출력할 때까지 무한 루프
       read_size = read(fd1, buf, MAX_BUF);  // buf에 fd1의 내용 입력(읽기)
       if(read_size == 0) {     // 읽은 내용이 없으면 = fd1의 내용을 전부 입력받았다면
           break;       // 무한 루프 종료
       }
       write_size = write(fd2, buf, read_size);     // buf에 읽어온 fd1의 내용을 fd2에 출력(쓰기) 
    }

    close(fd1);      // fd 닫기
    close(fd2);      // fd2 닫기
}