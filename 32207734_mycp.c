/**
 * mycp.c	: cp command program
 * @author	: Lee Heon
 * @email	: knife967@gmail,com
 * @version	: 1.0
 * @date	: 2022.11.04
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main (int argc, char *argv[]) {
	int fd_org, fd_target, read_size, write_size;
	char buf[MAX_BUF];
	struct stat st;

	// Usage Error
	if (argc != 3) {
		printf("USAGE: %s  original_file  copy_file_name\n", argv[0]);
		exit(-1);
	}
	
	// Open Original File
	fd_org = open(argv[1],O_RDONLY);
	// File Error
	if (fd_org < 0) {
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}
	// Store Permission of Original File
	stat(argv[1], &st);
	
	// Create Copy Target  File
	fd_target = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
	// File Error
	if (fd_target < 0) {
		printf("Can't open %s file with errno %d\n", argv[2], errno);
		exit(-1);
	}

	// Copy Contents to Target File
	while(1) {
		read_size = read(fd_org, buf, MAX_BUF);
		if (read_size == 0)
			break;
		write_size = write(fd_target, buf, read_size);
	}

	// Closs File
	close(fd_org);
	close(fd_target);

	return 0;
}
