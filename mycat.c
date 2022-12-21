/*

mycat.c: cat command program
author: 안정우
email: anjoungwo@gmail.com
version: 1.0
student id: 32212465
date: 2022-11-01
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //포직스 기본 입출력
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64 //버퍼 크기. 적정 크기의 버퍼를 정하는 것이 중요


/*
argc: 명령어가 몇 개 들어있냐
argument vector: 위의 것을 저장
*/

int main(int argc,char *argv[]){
	int fd, read_size, write_size;
	//read and write size..얼마나 읽고 쓸 건지
	char buf[MAX_BUF];
	if(argc!=2){
		printf("USAGE:%S file_name\n",argv[0]);
		/*cat은 뒤에 파일명까지 써야함
		argc=2가 아니면 오류처리*/
		exit(-1);
	}
	
	
	//argv[0]엔 명령어가 저장돼 있음
	fd=open(argv[1], O_RDONLY); 
	//read only..O_RDONLY은 파일을 열 수 없으면 -1을 반환한다
	
	if(fd<0){
		printf("Can't open %s file with errno %d\n",argv[1],errno);
		exit(-1);
	}
	while(1){
		read_size=read(fd,buf,MAX_BUF);
		if(read_size==0){
			break;
		}
		write_size=write(STDOUT_FILENO,buf,read_size);

	}
close(fd);
	
	return 0;
	
}
