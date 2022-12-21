#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#define MAX_BUF 1024

int main(int argc,char *argv[]){
	int in_fd, out_fd, read_size,write_size;
	char buf[MAX_BUF];
	if (argc != 3){
		printf("USAGE %s file name \n",argv[0]);
		exit(-1);
	}
	if(access(argv[2],F_OK)==0){
		printf("This file is already exist\n");
	}
	in_fd = open(argv[1], O_RDONLY);
	if(in_fd<0){
		printf("Can't open %s file with errno %d\n",argv[1],errno);
		exit(-1);
	}
	out_fd = creat(argv[2],0644);
	if (out_fd<0){
		printf("Can't open %s file with errno %d\n",argv[2],errno);
		exit(-1);
	}
	while(1){
		read_size = read(in_fd,buf,MAX_BUF);
		if (read_size == 0)
			break;
		write_size = write(out_fd,buf,read_size);
		if (write_size != read_size){
			printf("error\n");
		}
	}
	close(in_fd);
	close(out_fd);

	return 0;
}


