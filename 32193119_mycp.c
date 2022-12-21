/**
* file_test mycat.c: read data a file
* @author : lee seo bin
* @email:sltenic@naver.com
* @version:
* @ date: 2022 11 04
**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* fp = fopen(argv[1], "r");
    FILE* nfp = fopen(argv[2], "w");
    if (fp == NULL || nfp == NULL) {
        perror("fopen");
        return -1;
    }
    char buf[4096];
    int ret = 0;
    while (ret = fread(buf, sizeof(char), sizeof(buf), fp))
        fwrite(buf, 1, ret, nfp);
    fclose(fp);
    fclose(nfp);
    return 0;
}