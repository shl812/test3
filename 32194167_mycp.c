/*
* mycp.c: copy data and attributes from  original file and create copy file 
* author:Wonjun Jung
* email:32194167@dankook.ac.kr
* version:1.01
* date:2022.11.04
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#define maxbuf 64
int main(int argc, char *argv[])
{
int fd, fd1, reads,writes;
char tag[maxbuf];
struct stat buffer;
 if(argc!=3)
   {
        printf("usage:%s original, copy\n",argv[0]);
        exit(-1);
   }
fd=open(argv[1],O_RDONLY);
if(fd<0)
{
    printf("can't open %s file with errno %d\n", argv[1], errno);
    exit(-1);
}
fd1=open(argv[2],O_RDWR|O_CREAT|O_EXCL);
if(fd1<0)
{
    printf("can't open %s file with errno %d\n", argv[2], errno);
    exit(-1);
}
dup2(fd1, STDOUT_FILENO);
stat(argv[1], &buffer);
chmod(argv[2],buffer.st_mode);
while(1)
{
    reads=read(fd,tag,maxbuf);
    if(reads==0)
    {
        break;
    }
    writes=write(STDOUT_FILENO,tag,reads);
}
close(fd);
close(fd1);
return 0;
}
