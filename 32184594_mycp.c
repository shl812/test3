/**
 *mycp.c : Do not creat a file if the same name already exists in current directory
 	   and copy not only contents but also the attributes
 *author : Seongjin Choi
 *email  : chltjdwls294@naver.com
 *version : 1.0
 *date : 2022.10.31
**/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>


void f_err(int erno)
{
	switch(erno)
	{
		case ENOENT : printf("해당파일 존재X\n"); exit(0);
		case EACCES : printf("접근 퍼용된 파일X\n");exit(0);
    		case EROFS  : printf("읽기 전용 파일입니다"); exit(0);
		default : printf("모르는  파일입니다"); break;
	}
}
void make_writeFile(char *input_file, char *output_file)
{
	int read_size, write_size;
	int read_size1;

	char buf[1024];
	read_size= open(input_file,O_RDONLY);
	write_size = open(output_file, O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);

	while((read_size1 = read(read_size,buf,sizeof(buf))) >0)
		write(write_size,buf,read_size1);
}

void get_fileException(int argcn, char *arg1, char *arg2)
{
	if(argcn <4)
	{
		printf("대상파일 입력 X\n");
		exit(0);
	}
	if(access(arg1,F_OK)!=0)
	{
		printf("원본 파일 존재X\n");
		exit(0);
	}
	if(strcmp(arg1,arg2) ==0 )
	{
		printf("원본과 같습니다.\n");
		exit(0);
	}
}
int main(int argc, char **argv)
{
	int opt;
	char name[64];
	char answer ='h';

	if((opt =getopt(argc,argv,"b:f")) !=-1)	{
		switch(opt){
			case 'b':
				get_fileException(argc,argv[2],argv[3]);
				if(argc >3){
					
						if(access(argv[3],F_OK)==0){
						strcpy(name,argv[3]);
						strcat(name, "~");
						rename(argv[3],name);
						}
				make_writeFile(argv[2],argv[3]);

				}
				break;
			case 'f':
				get_fileException(argc, argv[2], argv[3]);
				if(access(argv[3],F_OK) ==0){
					if (unlink(argv[3])) {
				 		f_err(errno);
					}
				}
				make_writeFile(argv[2],argv[3]);
				break;
			case '?':
				printf("알수 없는 옵션입니다."); break;
		}
	}
	else{
		if(access(argv[1],F_OK) !=0) {
			printf("원본 파일이 존재하지 않습니다.\n");
			exit(0);
		}
		if(argc<3){
			printf("대상 파일이 입력되지 않았습니다.\n");
			exit(0);
		}

		if(access(argv[2],F_OK) == 0){
			while(answer =='y' | answer =='n'){
				printf("대상파일이 이미 존재합니다. 덮어쓰시겠습니까?");
				answer = getchar();
				if(answer == 'y'){
					if(unlink(argv[2])){
						f_err(errno);
					}
					make_writeFile(argv[1], argv[2]);
				}
				else if(answer =='n'){
					printf("복사 중단\n");
					exit(0);
				}
	    		 }
		}
		else {
			make_writeFile(argv[1],argv[2]);
		}
	}
	return 0;
}




					

