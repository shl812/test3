/*
 * mycp.c		: creates a dst_file(destination) and copies src_file(source) to dst_file
 * studentName	: Sung Yoo Hyun
 * studentNumber: 32212173
 * email		: jminfamous@dankook.ac.kr
 * date			: 2022.11.04
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 4096

int main(int argc, char *argv[])
{
	int infd, outfd, read_size, write_size, ch;
	char buf[MAX_BUF];
	
	// 0. notice USAGE if the argument count is not correct
	if (argc!=3)
	{
		printf("USAGE : %s src_file dst_file\n", argv[0]);
		exit(-1);
	}

	// 1. open the in-file descriptor for READING src_file
	infd=open(argv[1], O_RDONLY);
	if (infd<0)
	{
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}
	
	// 2. open the out-file descriptor for CREATING dst_file
	outfd=open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0664);
	if (outfd<0)
	{
		printf("Can't create %s file with errno %d\n", argv[2], errno);
		exit(-1);
	}
	
    // 3.	copies src_file to dst_file
	// 3-1. read src_file until EOF
	// 3-2. write on dst_file while read 
	while ((ch=read(infd, buf, MAX_BUF))>0)
	{
		if (write(outfd, buf, ch)!=ch)
		{
			printf("Can't write %s file\n", argv[2]);
			exit(-1);
		}
	}
	if (ch<0)
	{
		printf("Can't read from %s file\n, size = %d\n", argv[1], read_size);
		exit(-1);
	}
	
	// 4. close all file descriptor
	close(outfd);
	close(infd);

	return 0;
}