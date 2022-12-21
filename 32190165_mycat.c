#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]){
		char *p = argv[1];
        char buf[BUF_SIZE];
        int fdin;
	
        if(argc != 2){
                printf("error \n");
                exit(1);
        }

        fdin = open(p, O_RDONLY);
        if(fdin == -1){
                printf("error \n");
                exit(1);
        }


        read(fdin, buf, sizeof(buf));

        printf("%s", buf);
        close(fdin);
        return 0;
}
