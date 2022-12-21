/*

mycp.c: cat command program
author: 안정우
email: anjoungwo@gmail.com
version: 1.0
student id: 32212465
date: 2022-11-01
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //포직스 기본 입출력
#define MAX_BUF 64 //버퍼 크기. 적정 크기의 버퍼를 정하는 것이 중요








char fname[]="newfile.txt"; //새로 생성할 파일 이름
/*
argc: 명령어가 몇 개 들어있냐
argument vector: 위의 것을 저장
*/
int main(int argc,char *argv[]){
	struct stat sb;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        return 1;
    }
	int fd, fd1, read_size, write_size;
	//read and write size..얼마나 읽고 쓸 건지
	char buf[MAX_BUF];
	if(argc!=2){
		printf("USAGE:%S file_name\n",argv[0]);
		/*cat은 뒤에 파일명까지 써야함
		argc=2가 아니면 오류처리*/
		exit(-1);
	}
	
	
	//argv[0]엔 명령어가 저장돼 있음
	fd=open(fname, O_RDWR|O_CREAT|O_EXCL,0664); 
	fd1=open(argv[1], O_RDONLY); 
	
	//read and write..O_RDWR은 파일을 열 수 없으면 -1을 반환한다
	//O_CREAT로 파일 생성을 하되,
	//O_EXCL로 동일한 파일이 있으면 생성하지 않는다
	if(fd1<0){
		printf("Can't open %s file with errno %d\n",argv[1],errno);
		exit(-1);
	}

	while(1){
		read_size=read(fd1,buf,MAX_BUF);
		if(read_size==0){
			break;
		}
		write_size=write(fd,buf,read_size);
	}

	
	
	if(fd<0){
		printf("Can't open %s file with errno %d\n",argv[1],errno);
		exit(-1);
	}
	read_size=read(fd,buf,MAX_BUF); //데이터가 파일에 잘 적혔는지 확인한다
	printf("read_size= %d\n",read_size);
	write_size=write(fd,buf,read_size);


	FILE *fpo;
	fpo=fopen(fname,"a");
	fprintf(fpo,"\nI-node number:            %ld\n", (long) sb.st_ino);
	fprintf(fpo,"Mode:                     %lo (octal)\n", (unsigned long) sb.st_mode);
	fprintf(fpo,"Link count:               %ld\n", (long) sb.st_nlink);
	fprintf(fpo,"Ownership:                UID=%ld   GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
	fprintf(fpo,"Preferred I/O block size: %ld bytes\n",         (long) sb.st_blksize);
	fprintf(fpo,"Preferred I/O block size: %ld bytes\n",         (long) sb.st_blksize);
	
    fprintf(fpo,"File size:                %lld bytes\n",        (long long) sb.st_size);
    fprintf(fpo,"Blocks allocated:         %lld\n",              (long long) sb.st_blocks);
    fprintf(fpo,"Last status change:       %s", ctime(&sb.st_ctime));
    fprintf(fpo,"Last file access:         %s", ctime(&sb.st_atime));
    fprintf(fpo,"Last file modification:   %s", ctime(&sb.st_mtime));
	fclose(fpo);
close(fd);
		close(fd1);
	return 0;
}