// 32180360 kim kyung tae
// mycat.c copy file only data not permission
//


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#define MAX 64

int main(int argc, char* argv[]){
	int fd1;
	int fd2;
	int read_size;
	
	char buf[MAX];
	if(argc != 3){
		printf("USAGE : %s file copyfile\n",argv[0]);
		exit(1);
	}
	fd1= open(argv[1],O_RDONLY);
	if(fd1<0){
		printf("can't open %s file with errno %d\n", argv[1],errno);
		exit(-1);
	}

	fd2= open(argv[2],O_CREAT| O_EXCL | O_RDWR, 0600);
	if(fd2<0){
		printf("can't open %s file with errno %d\n", argv[2],errno);
		exit(-1);
	}
	while(1){
		read_size=read(fd1,buf,MAX);
		if(read_size==0) break;
		write(fd2,buf,read_size);
	}
	close(fd1);
	close(fd2);
	return 0;
}
