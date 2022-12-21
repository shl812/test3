/**
 *mycat.c	:cat command program
 *@author	:Seeun Kim
 *@email	:rlaserma1014@dankook.ac.kr
 *@version	:1.0
 *@date		:2022.10.31
**/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){
	int fd, read_size, write_size;
	struct stat st;
	char buf[MAX_BUF];

	if(argc != 2) {
		printf("USAGE: %s file_name\n", argv[0]);
		exit(-1);
	}

	if(stat(argv[1], &st) < 0){
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}
	if(!S_ISREG(st.st_mode)){
		printf("\"%s\" is not a file\n", argv[1]);
		exit(-1);
	}

	fd = open(argv[1], O_RDONLY);
	if(fd<0){
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}
	while(1){
		read_size = read(fd, buf, MAX_BUF);
		if(read_size == 0)
			break;
		write_size = write(STDOUT_FILENO, buf, read_size);
	}
	close(fd);
	return 0;
}
