/**
 * mycp.c 	   : program for copy 
 * @author 	   : 손우혁
 * @student_id : 32192206
 * @version    : 1.0
 * @date 	   : 2022-10-29
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>		//fstat을 쓰기 위한 해더파일
#include <sys/stat.h>		//fstat을 쓰기 위한 해더파일
#define MAX_BUF 32			//buffer의 크기를 32로 설정

int main(int argc, char* argv[]){
	int fd1, fd2, read_size, write_size;
	char buffer[MAX_BUF];
	struct stat f1;			//fd1의 파일정보를 저장할 구조체 변수
	if(argc != 3){			//인자가 3개가 아니면 Format Errot 출력
		printf("Format Error! %s original_file_name	copy_file_name\n", argv[0]);
		exit(-1);
	}
	//파일 2개중 하나라도 정상적으로 열리지 않으면 오류출력
	if((fd1 = open(argv[1], O_RDONLY)) < 0 || (fd2 = open(argv[2], O_WRONLY | O_CREAT |O_EXCL)) < 0){
		printf("Can not open file %s or %s with error number %d\n", argv[1], argv[2], errno);
		exit(-1);
	}
	//첫번째 인자의 파일의 상태정보를 얻어오는데 실패하면 오류 출력
	if(fstat(fd1, &f1) < 0){
		printf("Can not get status of file %s with error number %d\n", argv[1], errno);
		exit(-1);
	}
	//파일의 내용을 복사하는 코드
	while(read_size = read(fd1, buffer, MAX_BUF)){
		write_size = write(fd2, buffer, read_size);
		//write와 read에 문제가 있을 시 오류 출력
		if(write_size < 0 || read_size < 0){
			close(fd1);
			close(fd2);
			printf("Can not write(or read) file %s's contants with error number %d\n", argv[1], errno);
			exit(-1);
		}
	}
	//권한 설정에 실패하면 오류 출력
	if(fchmod(fd2, f1.st_mode) < 0){
		printf("Can not change file %s mode with error number %d\n", argv[2], errno);
		close(fd1);
		close(fd2);
		exit(-1);
	}
		
	
	close(fd1);
	close(fd2);
	return 0;
}