/**
    mycp.c : mycp program
    @author : Sungbeom Cho
    @email : sbcho98@naver.com
    @version : 1.0
    @date : 2022.11.04
 */

#include <stdio.h>       // standard input/output library
#include <stdlib.h>      // 문자열 변환, 사 난수 생성, 동적 메모리 관리 등
#include <unistd.h>      // POSIX 운영 체제 API에 대한 엑세스 제공 헤더 파일
#include <fcntl.h>       // file 제어 관련 -> open, read, write 등
#include <errno.h>       // 정적 메모리 위치에 저장된 오류 코드를 통해 오류 상태 보고 및 검색하기 위한 매크로 정의
#include <sys/stat.h>    // 파일 정보를 담고 있는 struct stat
#include <sys/types.h>   // defines a collection of typedef symbols and structures
#define MAX_BUF 64       // mycp가 복사할 수 있는 최대 크기: 64

int main(int argc, char* argv[]) {            // 해당 프로그램이 받는 인자는 argc: 문자열 갯수, argv: 문자열 리스트
    int fd1, fd2,read_size, write_size;       // 읽을 파일fd1, 쓸 파일 fd2, 읽은 크기, 쓴 크기를 저장할 read_size와 write_size
    char buf[MAX_BUF];                        // fd1의 내용을 저장할 리스트 buf
    struct stat attribute;                    // 파일의 상태 정보를 저장하는 구조체 stat
    
    if (argc != 3) {                          // 에러 처리, 커맨드는 "mycp" 문자열과 "읽을 파일", "쓸 파일" 3개여야함
        printf("USAGE: %s file_name\n", argv[0]);
        exit(-1);
    }
    
    fd1 = open(argv[1], O_RDONLY);            // argv[1]는 커맨드 중 "읽을 파일"을 나타냄, fd1에 읽기 전용으로 파일 열어서 저장
    
    if (fd1 < 0) {                            // fd1이 음수이면 어떠한 이유로 파일 여는 것을 실패했다는 뜻, errno.h의 errno를 통해 에러확인
        printf("Can't open %s file with errno %d\n", argv[1], errno);
        exit(-1);
    }
    
    // "읽을 파일"의 권한 가져오기를 실패했을때 에러 출력 코드 stat()은 성공 시 0, 실패 시 -1 반환
    if(stat(argv[1], &attribute) == -1) {
        printf("getting attribute error\n");
        exit(-1);
    }
    
    mode_t fd1_permission = attribute.st_mode;               // fd1의 권한을 저장
    fd2 = open(argv[2], O_RDWR | O_CREAT, fd1_permission);   // "읽을 파일" open, 해당 파일이 없으면 생성 가능, fd1의 권한과 동일하게 부여
    dup2(fd2, STDOUT_FILENO);                                // 원래 터미널을 나타내는 STDOUT_FILENO를 "쓸 파일"을 나타내게 함
    
    // offset이 읽을 파일의 맨 끝을 가리킬 때까지
    while(1) {
        read_size = read(fd1, buf, MAX_BUF);      // buf 리스트에 MAX_BUF 크기만큼 fd의 내용을 저장
        if (read_size == 0)                       // offset이 끝을 가리키거나 읽을 내용이 없으면 break
            break;
        write_size = write(STDOUT_FILENO, buf, read_size);   // buf 리스트에 읽은 내용들을 "쓸 파일"에 출력
    }
    
    close(fd1);    // "읽을 파일" 닫기
    close(fd2);    // "쓸 파일" 닫기
    
    return 0;
}
