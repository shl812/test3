/*
 * mycp.c : making command 'cp' myself
 * @author : Jeong kyu won
 * @student_id : 32204027
 * @email : 32204027@dankook.ac.kr
 * @version : 1.0
 * @date : 2022. 10. 31.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 32

int main(int argc, char* argv[]){
	
	int fd_origin, fd_copy, read_size, write_size;
	char buf[MAX_BUF];
	struct stat att_origin;	//to copy attributes of original file
	struct utimbuf time_att_origin; //to copy time attributes of original file

	if(argc != 3){
		printf("USAGE : %s original_file_name copy_file_name\n", argv[0]);
		exit(-1);
	}//endif

	fd_origin = open(argv[1], O_RDONLY);
	fd_copy = open(argv[2], O_WRONLY|O_CREAT|O_EXCL, 0000);

	if(fd_origin < 0){
		printf("\"mycp\" command is stopped with error number %d\n", errno);
		exit(-1);
	}//endif

	if(fd_copy < 0){
		printf("\"mycp\" command is stopped with error number %d\n", errno);
		exit(-1);
	}//endif

	if(fstat(fd_origin, &att_origin) < 0){
		printf("fstat error code : %d\n", errno);
		exit(-1);
	}//endif
	
	//copy data
	while(1){
		read_size = read(fd_origin, buf, MAX_BUF);
		if(read_size==0){
			break;
		}//endif
		write_size = write(fd_copy,buf,read_size);
	}//endwhile

	//copy file access permission
	if(fchmod(fd_copy, att_origin.st_mode) < 0 ){	//access permission copy
		printf("fchmod error code : %d\n", errno);
		exit(-1);
	}//endif
	
	time_att_origin.actime=att_origin.st_atime;	//file access time copy
	time_att_origin.modtime=att_origin.st_mtime;	//file modification time copy 
	
	//copy file access time, file modification time
	if(utime(argv[2], &time_att_origin) < 0 ){
		printf("utime error code : %d\n", errno);
		exit(-1);
	}//endif
	
	//copy uid, gid of original file to copy file
	if(fchown(fd_copy, att_origin.st_uid, att_origin.st_gid) < 0){
		printf("chown error code : %d\n", errno);
		exit(-1);
	}//endif
	
	close(fd_origin);
	close(fd_copy);
	return 0;
}//endmain
