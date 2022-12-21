/**
 * mycp.c	: copy command program
 * os		: Ubuntu-20.04
 * @author	: 김형중 32191305 소프트웨어학과
 * @class 	: 시스템 프로그래밍 2분반
 * @email	: gudwnd1113@naver.com
 * @version : 1.0
 * date		: 2022.10.31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>

#define MAX_BUF 64

int main(int argc, char *argv[]){
	int fd_c, fd_p, read_size, write_size;
	char buf[MAX_BUF];

	struct stat attrib;  // 원본 파일의 속성을 저장하는 구조체
	struct utimbuf time_attr;  // 원본 파일의 시간 속성을 저장하는 구조체
	struct stat file_type;  // 복사본 파일의 속성을 저장하는 구조체

	// 올바르지 못한 명령어 사용에 대한 예외 처리
	if(argc != 3){
		printf("USAGE : \n%s file_to_copy file_to_paste\
				\n%s file_to copy directory_to_paste", argv[0], argv[0]);
		exit(-1);
	}

	fd_c = open(argv[1], O_RDONLY);  // file to copy
	if(fd_c < 0){
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}

	if(fstat(fd_c, &attrib) < 0){  // 첫번째 인자(원본)의 속성을 구조체에 저장
		printf("Can't get %s file attributes with errno %d\n", argv[1], errno);
		exit(-1);
	}

	// 두번째 인자가 유효한 타입(디렉토리, 파일)인지 확인 
	if (access( argv[2], F_OK) != -1) {
		if(lstat(argv[2], &file_type) < 0){  // 두번째 인자의 속성을 구조체에 저장
			printf("Can't get %s file type with errno %d\n", argv[2], errno);
			exit(-1);
		}

		// 디렉토리일 경우 파일 경로의 형태로 인자 수정
		if (S_ISDIR(file_type.st_mode)){
			argv[2] = strcat(argv[2], "/");
			argv[2] = strcat(argv[2], argv[1]);
			}

		//  파일이 아닌 다른 타입일 경우 예외 처리
		else if (S_ISREG(file_type.st_mode) != 1){
			printf("Invalid file type %s\n", argv[2]);
			exit(-1);
		}
	}

	// 복사본 파일 생성 시 mode를 원본 파일의 권한으로 지정
	fd_p = open(argv[2], O_RDWR | O_CREAT | O_EXCL, attrib.st_mode);
	if(fd_p < 0){
		printf("Can't creat %s file with errno %d\n", argv[2], errno);
		exit(-1);
	}

	while(1){
		read_size = read(fd_c, buf, MAX_BUF);
		if(read_size < 0){
			printf("Can't read from file %s, size = %d\n", argv[1], read_size);
			exit(-1);
		}
		else{
			if (read_size == 0)
				break;
			write_size = write(fd_p, buf, read_size);
		}
	}

	// 원본의 액세스 시간, 수정한 시간 구조체에 저장 후 복사본 속성에 복사
	time_attr.actime = attrib.st_atime;
	time_attr.modtime = attrib.st_mtime;
	if(utime(argv[2], &time_attr) < 0){
		printf("Cant' copy %s time information to %s with errno %d\n", argv[1], argv[2], errno);
		exit(-1);
	}

	//if(fchmod(fd_p, attrib.st_mode) < 0){
	//	printf("Can't copy %s file attributes with errno %d\n", argv[1], errno);
	//	exit(-1);
	//}

	close(fd_c);
	close(fd_p);

	return 0;
}
