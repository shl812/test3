/**
* mycp.c		: cp 명령어를 구현하는 프로그램
* @author		: 윤예진
* date			: 2022.11.04
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>				//리눅스 <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 100


int main(int argc, char* argv[])
{
	int orgn_fd, cp_fd, read_size, write_size, orgn_path, cp_path;
	char buf[MAX_BUF];
	struct stat* statfile;

	if (argc < 3) {
		printf("USAGE: %s file_name\n", argv[0]);
		exit(-1);
	}
	else if (argc > 3) {
		printf("Invalid format\n");
		exit(-1);
	}

	orgn_path = 1;
	cp_path = 2;

	//원본 파일 open
	orgn_fd = open(argv[orgn_path], O_RDONLY, 0664);

	//파일 열기 실패 시 종료
	if (orgn_fd < 0) {
		printf("Can't open %s file with errno11 %d\n", argv[orgn_path], errno);
		exit(-1);
	}

	//복사할 파일 생성
	cp_fd = open(argv[cp_path], O_RDWR | O_CREAT | O_EXCL, 0664);

	//파일 생성 실패 시 종료
	if (cp_fd < 0) {
		printf("Can't create %s file with errno22 %d\n", argv[cp_path], errno);
		exit(-1);
	}

	//파일내용 복사
	while (1) {
		read_size = read(orgn_fd, buf, MAX_BUF);
		if (read_size == 0)
			break;
		write_size = write(cp_fd, buf, read_size);
	}

	//원본 파일로부터 파일 속성 가져오기
	if (stat(argv[orgn_path], statfile) < 0) {
		printf("Can't get %s file stat with errno %d\n", argv[orgn_path], errno);
		exit(-1);
	}

	//원본 파일로부터 복사할 파일로 권한 복사
	chmod(argv[orgn_path], statfile->st_mode);
	
	close(orgn_fd);
	close(cp_fd);

	return 0;
}ㄴ