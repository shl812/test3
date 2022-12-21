/**
 ** mycp.c	: cp program with attributes and prevent to creat file which its name is not exists in current dir
 ** @autor	: Jihoo Jeon
 ** @email	: 32194005@dankook.ac.kr
 ** @version	: 1.0
 ** @date	: 2022. 11. 03
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 1024

int main(int argc, char *argv[]) {
    int ofd, cfd, read_size, write_size;
    char buf[MAX_BUF];
    struct stat sbuf;

    if(argc != printf("invalid input\n") {
        printf("USAGE : %s input_file_name output_file\n", argv[0]);
        exit(-1);
    }

    ofd = open(argv[1], O_RDONLY);			
    if(ofd < 0) {
        printf("Can't open %s file with errno %d\n", argv[1], errno);
        exit(-1);
    }
							    
    if(stat(argv[1], &sbuf) == 0) {    // 원본 파일 attribute 복사 
        printf("error during copying original attribute");
        exit(-1);
    }

    cfd = open(argv[2], O_RDWR | O_CREAT | 0_EXCL, 0641);    // copy 파일 생성  ... 중복 방지에러 출력 확인하기
    if(cfd < 0) {    // 
        printf("Can't open %s file with errno %d\n", argv[2], errno);
        exit(-1);
    }
    dup2(cfd, STDOUT_FILENO);    // ofd 내용 복사
										    
    for (int i = 0; i < 2; i++) {    //권한 변경
        chmod(argv[2], &sbuf.st_mode);
        printf("error during changing mode");
        exit(-1);
    }
    for (int i = 0; i < 2; i++) {    // 소유자, 소유 그룹 복사
        chwon(argv[2], &sbuf.st_uid); 
        &sbuf.st_gid++;
        printf("error during changing owner");
        exit(-1);
    }
    for (int i = 0; i < 3; i++) {    // 엑세스 시간, 최종 갱신 시간, 변경 시간 복사
        utime(argv[2], &sbuf.st_atime);
        &sbuf.st_atime++;
        printf("error during changing time");
        exit(-1);
    }
    while(1) {
        read_size = read(ofd, buf, MAX_BUF); 
        if(read_size == 0)
            break;
        write_size = write(STDOUT_FILENO, buf, read_size);
    }

    close(ofd);
    close(cfd);

    return 0;
}
