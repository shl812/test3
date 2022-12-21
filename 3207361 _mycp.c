/**
 * mycp.c : cp command program
 * @author : Yunji Park
 * @email : pyjione@naver.com
 * @date : 2022.11.04
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64
int main(int argc, char* argv[]) {
        int fd1, fd2;
        struct stat sb;
        mode_t mode;
        if(argc != 3){
                printf("USAGE : %s file_name\n",argv[0]);
                exit(-1);
        }
        fd1= open(argv[1],O_RDONLY);
        fd2 = open(argv[2],O_RDWR|O_CREAT|O_EXCL,0644);
 
        if(fd1 == -1 || fd2 == -1){
            printf("Can't open %s file with errno %d\n",argv[1],errno);
                    exit(-1);
        }
        if (fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL,0644) < 0) {
                fprintf(stderr, "파일 %s가 이미 존재합니다", argv[2]);
                exit(-1);
            }
        char *buffer[MAX_BUF];
        int nb;
 
        while(nb = read(fd1, buffer, MAX_BUF)){
                write(fd2, buffer ,nb);
        }
        mode = sb.st_mode;
        chmod(argv[2], mode);
        printf("성공\n");
        close(fd1);
        close(fd2);
        return 0;
}
