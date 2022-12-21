/**
* mycp.c	:mycp command program
* @author	:32214027 정규민
* @email	:32214027@dankook.ac.kr
* @version	:1.0
* @date		:2022. 11. 4
**/
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int mycp(const char* read_file, const char* write_file) {

    FILE* readf, * writef;
    char buf[1024];
    size_t size;
    if (!strcmp(read_file, write_file))   
        return 2;
    if (NULL == (readf = fopen(read_file, "rb")))    
        return 3;
    if (NULL == (writef = fopen(write_file, "wb"))) {
        fclose(readf);
        return 4;
    }
    while (0 < (size = fread(buf, 1, sizeof(buf), readf))) {
        if (0 == fwrite(buf, 1, size, writef)) {
            fclose(readf);
            fclose(writef);
            unlink(write_file);
            return 5;
        }
    }
    fclose(readf);
    fclose(writef);

    return 0;
}

int   main(int argc, char** argv)
{
    if (3 > argc) {
        printf("mycp: '%s' 다음에 대상 파일 명령이 누락됨\n",argc);
        printf("Try 'mycp --help' for more information");
        return 1;
    }

    switch (mycp(argv[1], argv[2])) {
    case   2: printf("mycp: '%s'와 '%s'는 같은 파일\n",argv[1],argv[2]); break;
    case   3: printf("mycp: '%s'를 설명할 수 없음: 그런 파일이나 디렉터리가 없습니다\n",argv[1]); break;
    case   4: printf("mycp: '%s'파일을 생성할 수 없음\n",argv[2]); break;
    case   5: printf("mycp: '%s'파일을 쓸 수 없음\n",argv[2]); break;
    }
    return 0;
}