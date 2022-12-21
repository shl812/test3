/**
* mycp.c : cp command program
* @author : Park Ji Woo
* * @email: 32211862@dankook.ac.kr
* * @version : 1.0
* * @date : 2022. 11. 02
* **/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64
int main(int argc, char *argv[]) {
	int fd1, fd2, read_size, write_size;
	char buf[MAX_BUF];
	// 인자가 3개인지 확인 
	if (argc != 3) {
		printf("잘못된 입력 방식입니다.\n");
		exit(-1);
	}
	// 복사하려는 파일이 없는 경우
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0) {
		printf("없는파일이여서 파일을 열 수 없습니다\n");
		exit(-1);
	}
	// 파일 이름이 이미 있는 경우
	fd2 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0664);
	if (fd2 <0) {
		printf("이미 복사하려는 파일이름이 존재합니다. \n");
		exit(-1);
	}
	while(1) {
		read_size = read(fd1, buf, MAX_BUF);
		if (read_size == 0)
			break;
		write_size = write(fd2, buf, read_size);
	}
	close(fd1);
	close(fd2);
}
