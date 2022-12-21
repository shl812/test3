/**
* mycp.c	: cp command program
* @studentID: 32211334
* @author	: Hwanhee Kim
* @email	: khh5347@dankook.ac.kr
* @date		: 2022. 11. 01
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[]) {
	int fd, fd1, read_size, write_size;
	char buf[MAX_BUF];
	struct stat attribute;	// 파일 권한 저장 stat 구조체 선언

	// 입력 서식에 맞지 않을 경우 서식 출력
	if(argc != 3) {
		printf("USAGE : %s input_file_name output_file_name\n", argv[0]);
		exit(-1);
	}

	// 복사될 파일 read only 열기
	fd = open(argv[1], O_RDONLY);
	// 파일이 없을 시 오류
	if(fd < 0) {
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}
	
	// 입력한 파일의 권한 가져오기 & 실패 시 오류
	if(stat(argv[1], &attribute) < 0) {
		printf("Can't get %s file's attribute with error %d\n", argv[1], errno);
		exit(-1);
	}
	
	// 복사할 파일 [write only | 없으면 생성, 있으면 생성X] 열기
	fd1 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, attribute.st_mode);
	
	// 파일 내용 출력
	while(1) {
		read_size = read(fd, buf, MAX_BUF);
		if(read_size == 0)	// 출력할 내용이 더이상 없을 시 종료
			break;
		write_size = write(fd1, buf, read_size);
	}
	close(fd);
	close(fd1);

	return 0;
}