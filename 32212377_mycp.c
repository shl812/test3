/**
 * mycp.c		: copy command program
 * @author		: HyeounBin Shin
 * email		: tlsgusqls120@naver.com
 * @version		: 1.0
 * data			: 2022. 10. 30
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){
	int fd_in, fd_out, read_size;
	struct stat sbuf;
	char buf[MAX_BUF];
	
	if (argc != 3) {
		printf("USAGE : %s file_name\n", argv[0]);
		exit(-1);
	}
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0666);
	if (fd_in < 0) {
		printf("Can't open %s file with erro %d\n", argv[1], errno);
		exit(-1);
	}
	if (fd_out < 0) {
		printf("Can't open %s file with erro %d\n", argv[2], errno);
		exit(-1);
	}
	
	fstat(fd_in, &sbuf);
	fchmod(fd_out, sbuf.st_mode);
	
	while(1){
		read_size = read(fd_in, buf, MAX_BUF);
		if (read_size == 0) break;
		write(fd_out, buf, read_size);
	}
	
	close(fd_in);
	close(fd_out);

	return 0;
}