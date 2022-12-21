/**
* mycp.c : copy command program
* author : Jiyun Song
* @email : 32202341@dankook.ac.kr
* @version : 1.0
* date : 2022.10.26
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_BUF 256

char fname[] = "newfile.txt";
struct stat sts; // 파일 정보 저장할 구조체 생성

int main(int argc, char *argv[]) {
	int fd_origfile, fd_newfile, read_size, write_size;
	char buf[MAX_BUF];
	
	if (argc!=2) {
		printf("USAGE : %s filename\n", argv[0]);
		exit(-1);
	}
	
	fd_origfile=open(argv[1], O_RDONLY);
	fstat(fd_origfile, &sts); // 파일의 상태 및 정보를 얻는 함수 fstat(fd, struct stat *buf) > 구조체 buf에 파일 상태정보 저장함
	fd_newfile=open(fname, O_RDWR | O_CREAT | O_EXCL, sts.st_mode); // .st_mode: 파일의 종류 및 접근 권한
	
	if (fd_origfile<0) {
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}
	if (fd_newfile<0) {
		printf("Can't create this %s file with errno %d\n", fname, errno);
		exit(-1);
	}
	
	while(1) {
		read_size = read(fd_origfile, buf, MAX_BUF);
		if (read_size==0) {
			break;
		}
		write_size = write(fd_newfile, buf, read_size);
	}
	
	close(fd_origfile);
	close(fd_newfile);
	
	return 0;
}
