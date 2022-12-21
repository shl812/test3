/**
*mycat.c    :cat command program
*@author    :Kim Boseung
*@email     :kbskbs1102@gmail.com
*@version   :8.0.1453
*@data      :2022.11.03
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char* argv[]) {
     int fd_in, fd_out, read_size, write_size;
     char buf[MAX_BUF];
     struct stat sbuf;

     if (argc != 3) {
         printf("USAGE : %s origin_file_name new_file_name \n", argv[0]);
        exit(-1);
	 }
     fd_in = open(argv[1], O_RDONLY);
     if (fd_in < 0) {
         printf("Can't open %s file with errno %d\n", argv[1], errno);
         exit(-1);
	 }
     fd_out = open(argv[2], O_RDWR | O_CREAT, 0666);
     if (fd_out < 0) {
         printf("Can't open %s file with errno %d\n", argv[2], errno);
         exit(-1);
	 }
     fstat(fd_in, &sbuf);
     fchmod(fd_out, sbuf.st_mode);

     while (1) {
         read_size = read(fd_in, buf, MAX_BUF);
         if (read_size == 0) break;
         write_size = write(fd_out, buf, read_size);
	 }
     close(fd_in);
     close(fd_out);
     return 0;
}