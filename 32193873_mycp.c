/**
	* name : siwoo Jang
	* email : jangsiwoo@dankook.ac.kr
	* date : 2022.11.04
**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 4096

int main(int argc,char *argv[]){
	
		int fd1, fd2, n;
		char buf[MAX_BUF];
		struct stat st;
		
		if (argc != 3) {
			fprintf(stderr, "Directions: %s file1 file2\n",argv[0]);
			exit(1);
		}
	
		if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
			perror(argv[1]);
			exit(2);
		}
	
		fstat(fd1, &st);
        
		fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC|O_EXCL,st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
	
	
		if ( fd2 == -1) {
			perror(argv[2]);
			exit(3);
		}
		
	
		while ((n = read(fd1, buf, MAX_BUF)) > 0 )
			write(fd2,buf,n);
	
		exit(0);
	
}