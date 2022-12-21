/**
*mycp.c	: duplicates file
*@author	: 32160705 Seonghyun Kim
*@email		: downshiftkor@naver.com
*@version	: 1.0
*@date		: 2022.11.03
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>


#define MAX_BUF 64

int main(int argc, char *argv[]) {
    int input_fd, output_fd, r_size;
	struct stat att;
    char buf[MAX_BUF];

	
input_fd = open(argv[1], O_RDONLY);
stat(argv[1], &att);
mode_t o_permission = att.st_mode;
		
output_fd = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,o_permission);

while ((r_size = read(input_fd, buf, MAX_BUF)) > 0)
	 write(output_fd, buf, r_size);
}



