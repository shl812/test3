#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#define MAX 256
void main(int argc,char* argv[]){

	int fd1, fd2, r_size;
	char buf[MAX];
	struct stat att1;//stat 구조체선언  mode_t st_mode로 파일 권한을 가져오기위해 

	//쓰기잘못	
	if(argc != 3){
		printf("ERROR USAGE : %s \"original_file\" \"copy_file\" \n",argv[0]);
		exit(-1);}
	//원래 파일 열기
	fd1 = open(argv[1],O_RDONLY);
	//파일 open 실패시
	if(fd1 < 0){
		printf("can't open file\n");
		exit(-1);}
	//새로만들 파일이 이미 있을경우
	if (errno == 17) {
      	printf("%s exist \n", argv[2]);
      	exit(-1);
   }
	
	mode_t att2 = att1.st_mode;//원래 파일의 st_mode를 가져옴
	

	fd2 = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,att2);//쓰기로 읽고 권한을 원래파일의 권한을 줌
	//파일 open 실패시
	if(fd1 < 0){
                printf("can't open file\n");
                exit(-1);}
	//파일끝까지 읽고 씀
	while((r_size = read(fd1,buf,MAX)) >0){
		write(fd2,buf,r_size);
	}
}