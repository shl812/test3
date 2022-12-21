//homework3.c	: homework3
//author	: Juan Mun
//email		: timidity@kakao.com
//From Homework3 in Linux Env.
//date		: 2022.11.04

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#define MAX_BUF 64


int main(int argc, char *argv[]){
	int fd, fd2, read_size, write_size;
	struct stat statbuf;
	char buf[MAX_BUF];
	
	//mycat
	if(strcmp(argv[1], "mycat") == 0){
		if(argc != 3){
			printf("my cat argument error, required arguments: 2, inserted arguments: %d\n", argc);
			exit(-1);
		}
		fd = open(argv[2], O_RDONLY);
		if(fd < 0) {
			printf("Can't open \"%s\" file with errmo %d\n", argv[1], errno);
			exit(-1);
		}

		while(1){
			read_size = read(fd, buf, MAX_BUF);
			if(read_size == 0)
				break;
			write_size = write(STDOUT_FILENO, buf, read_size);
		}

	close(fd);
	}

	//mycp
	else if(strcmp(argv[1], "mycp") == 0){
		if(argc != 4){
			printf("argument error, required arguments:4, inserted arguments: %d", argc);
			exit(-1);
		}

		fd = open(argv[2], O_RDONLY);
		if(fd < 0) {
                        printf("Can't open \"%s\" file with errmo %d\n", argv[1], errno);
                        exit(-1);
		}

		fd2 = open(argv[3], O_RDWR | O_CREAT | O_EXCL, 0664);
		if(fd2 < 0) {
			printf("Can't open \"%s\" file with errmo %d\n", argv[1], errno);
			exit(-1);
		}

		while ((read_size = read(fd, buf, MAX_BUF)) > 0) {
			if(write(fd2, buf, read_size) != read_size) {
		 		 printf("Can't write \"%s\" file with errno %d\n", argv[2], errno);
				 exit(-1);
			}
		}
		close(fd);
		close(fd2);
		
		if(stat(argv[2], &statbuf) < 0) {
			 printf("Can't bring \"%s\" file attributes with errno %d\n", argv[2], errno);
			exit(-1);
		}
		if(chown(argv[3], statbuf.st_uid, statbuf.st_gid) < 0){
			printf("Can't bring \"%s\" file attributes with errno %d\n", argv[2], errno);
                        exit(-1);
		}
		if (chmod(argv[3], statbuf.st_mode) < 0) {
			printf("Can't bring \"%s\" file attributes with errno %d\n", argv[2], errno);
                        exit(-1);
		}
	}
	else{
		printf("%d %s\n", argc, argv[1]);
	}
	return 0;
}