/* 
HW3 2022.11.04
mycp.c : copy program by JisunPark, 32211852@dankook.ac.kr
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char* argv[]) {
	int fd_1, fd_2, read_size, write_size;
	int fd_2_attribute;
	char buf[MAX_BUF];
	struct stat attribute;
	
	// 파일속성을 attribute에 저장하고, 접근권한을 부여
	stat(argv[1], &attribute);
	fd_2_attribute = attribute.st_mode;
	
	// 인자 갯수가 잘못되었을 경우
	if(argc != 3) {
		printf("잘못된 입력 형식입니다.\n");
		exit(0);
	}
	
	fd_1 = open(argv[1], O_RDONLY);
	if (fd_1 < 0) {		// 파일을 못읽었을 경우
		printf("파일을 열 수 없습니다.\n");
		exit(0);
	}
	
	if (stat(argv[1], &attribute) == -1) {		// fd_1 파일의 속성 가져오기 실패
		printf("속성을 가져올 수 없습니다.");
		exit(0);
	}
	
	fd_2 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, fd_2_attribute);
	if (fd_2 < 0) {
		printf("이름이 중복되었습니다.");
		exit(-0);
	}
	
	while (1) {
		read_size = read(fd_1, buf, MAX_BUF);
		if (read_size < 0) {
			printf("Error");
		}
		if (read_size == 0) {
			break;
		}
		write_size = write(fd_2, buf, read_size);
	}
	
	chmod(argv[2], fd_2_attribute);
	close(fd_1);
	close(fd_2);
	
	return 0;
}