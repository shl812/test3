/**
 *  mycp.c : make a command
 *  @author : 32214684 3분반 최지원
 *  @email : belle021202@naver.com
 *  @version : 1.0
 *  @date : 2022. 10. 30
 *  @environment: goorm ide
**/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#define MAX_BUF 64

int main(int argc, char *argv[])
{
    int fd, fd1, read_size, write_size;
    struct stat sb;
    char buf[MAX_BUF];
    struct utimbuf ubuf;

    if (argc != 3) //인자 개수 확인
    {
        printf("USAGE : %s original_file_name copy_file_name\n", argv[0]);
        exit(-1);
    }
    fd = open(argv[1], O_RDONLY); //file descripter 가져오기
    if (fd < 0)
    {
        printf("Can't open %s file with errno %d\n", argv[1], errno);
        exit(-1);
    }
    if (fstat(fd, &sb) == -1) //argv[1] mode 정보 가져오기
    {
        printf("fstat error with errno %d\n", errno);
        close(fd);
        exit(-1);
    }
    if (S_ISDIR(sb.st_mode))
    {
        printf("error\n");
        close(fd);
        exit(-1);
    }
    fd1 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, sb.st_mode);
    if (fd1 < 0)
    {
        printf("Can't create %s file with errno %d\n", argv[2], errno);
        close(fd);
        exit(-1);
    }
    //mode 바꿔주기
    if (chmod(argv[2], sb.st_mode) == -1)
    {
        printf("Can't change mode with errno %d\n", errno);
    }
    dup2(fd1, STDOUT_FILENO);
    while (1)
    {
        read_size = read(fd, buf, MAX_BUF);
        if (read_size == 0)
            break;
        write_size = write(STDOUT_FILENO, buf, read_size);
    }
    //time 바꿔주기 -> 최종 접근 및 최종 수정 시간 변경
    ubuf.actime = sb.st_atim.tv_sec; //st_atimespec
    ubuf.modtime = sb.st_mtim.tv_sec; //st_mtimespec
    if (utime(argv[2], &ubuf) == -1)
    {
        printf("utime error: %d\n", errno);
        close(fd);
        close(fd1);
        exit(-1);
    }
    //uid, gid 변경 sb.st_uid, sb.st_gid
    chown(argv[2], sb.st_uid, sb.st_gid);

    close(fd);
    close(fd1);
    return 0;
}