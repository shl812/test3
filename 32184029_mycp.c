//단국대 소프트웨어학과 18학번 전준익(32184029)
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define M 64

int main(int argc, char *argv[]){
int sz, f1, f2;
char buffer[M];
if(argc != 3){
printf("USAGE : %s filename copyfilename\n",argv[0]);
exit(-1);

}

f1 = open(argv[1], O_RDONLY);
f2 = open(argv[2],O_CREAT | O_RDWR | O_EXCL,0664);

while(1){
sz = read(f1,buffer,M);
if(!sz) break;
write(f2,buffer,sz);
}

close(f1);
close(f2);
return 0;

}


