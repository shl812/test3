/*
mycp.c		: cp command program
@author		: Dongyoung Kim
@email		: dmh258@naver.com
@version	: 1.0
@date		: 2022. 11. 04
@studentID	: 32190461
@major		: software
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE 64

void copy_file(char *name1, char *name2){
	int fd1, fd2, n;
	char buf[BUFSIZE];
	
	if((fd1=open(name1, O_RDONLY)) < 0) {
		printf("Can't open %s file with errno %d\n", name2[1], errno);
		exit(-1);
	}
	
	if((fd2 = open(name2, O_WRONLY | O_CREAT)) < 0){
		printf("Can't open %s file with errno %d\n", name2[1], errno);
		exit(-1);
	}
	
	while((n = read(fd1, buf, BUFSIZE)) > 0){
		write(fd2, buf, n);
	}
	
	close(fd1);
	close(fd2);
}

int main(int argc, char *argv[]){
	copy_file(argv[1], argv[2]);
	return 0;
}