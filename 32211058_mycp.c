// 32211058 김준명
// 2022-11-03
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[])
{
	int fdread, fdwrite, read_size, write_size;
	char buf[MAX_BUF];

	if (argc != 3) {		// 인자의 개수가 틀린 경우
		printf("USAGE : %s file_name1 file_name2\n", argv[0]);
		exit(-1);			// 올바른 사용법을 명시
	}

	// 첫번째 인자에 해당하는 파일 읽어들이기
	fdread = open(argv[1], O_RDONLY);

	// 파일 열기에 실패한 경우 에러코드와 함께 실행 종료
	if (fdread < 0) {
		printf("Can't open %s file with errno %d\n", argv[1], errno);
		exit(-1);
	}

	// 두 번째 인자에 해당하는 파일 생성, 단, 이미 있는 파일일 시 종료
	fdwrite = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0664);
	if (fdwrite < 0) {
		printf("Can't open %s file with errno %d\n", argv[2], errno);
		exit(-1);
	}

	// fdread가 읽은 정보 읽어들이기
	read_size = read(fdread, buf, MAX_BUF);

	// 읽은 사이즈 만큼 두번째 인자에 해당하는 파일에 작성
	write_size = write(fdwrite, buf, read_size);

	close(fdread); // file descriptor 닫기
	close(fdwrite);

	return 0;
}
