/**
 * mycp.c	: copy data form a file
 @author	: Jinoh Park
 @email		: qkrwlsdh03@naver.com
 @version	: 1.0
 @date		: 2022. 10. 04
**/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define MAX 64

void main(int argc,char* argv[])
{

	int original copy, r_size;
	char buf[MAX];
	struct stat attribute;//stat 구조체선언  mode_t st_mode로 파일 권한을 가져오기위해 

	//쓰기잘못	
	if(argc != 3)
	{
		printf("USAGE : %s \"original_file\" \"copy_file\" \n",argv[0]);
		exit(-1);
	}
	//orignal 파일 열기
	original = open(argv[1],O_RDONLY);
	//파일 open 실패시
	if(original < 0)
	{
		printf("can't open file\n");
		exit(-1);
	}
	
	if(stat(argv[1], &attribute)==-1)
	{
		printf("getting attribute error\n");	//original file 속성가져옴 실패시 에러
		exit(-1);
	}
	mode_t original_permisson = attribute.st_mode;//original의 st_mode를 가져옴
	
	copy = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,original_permisson);//쓰기로 읽고 권한을 original파일의 권한을 줌
	
	//파일 open 실패시
	if(original < 0)
	{
        printf("can't open file\n");
        exit(-1);
	}
	//파일끝까지 읽고 씀
	while((r_size = read(original,buf,MAX)) >0)
	{
		write(copy,buf,r_size);
	}
}