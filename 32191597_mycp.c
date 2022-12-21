/*
    학번 : 32191597
    이름 : 박민규
    작성일자 : 2022/11/01
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_BUF 64

char *flip_Str(char *str);

struct mode_t
{
    char user;
    char group;
    char other;
};

int main(int argc, char **argv)
{
    int fd_copy, fd_paste, read_size, write_size;
    char buf[MAX_BUF];
    char str[10];
    char flip[10];
    struct stat mode;
    struct mode_t copymode;

    stat(argv[1], &mode);
    sprintf(str, "%o", mode.st_mode);
    strcpy(flip, flip_Str(str));
    // flip[2] <- user 권한
    // flip[1] <- group 권한
    // flip[0] <- other 권한
    copymode.user = flip[2];
    copymode.group = flip[1];
    copymode.other = flip[0];
    printf("user : %c group : %c other : %c\n", copymode.user, copymode.group, copymode.other);
    char arg[4] = {'0', copymode.user, copymode.group, copymode.other};
    int num_arg[4] = {
        0,
    };
    int i;
    for (i = 0; i < 4; i++)
    {
        num_arg[i] = arg[i] - '0';
    }
    int paste_mode;
    paste_mode = num_arg[3];
    paste_mode = paste_mode | (num_arg[2] << 3);
    paste_mode = paste_mode | (num_arg[1] << 6);
    paste_mode = paste_mode | (num_arg[0] << 9);
    printf("paste : %o\n", paste_mode);

    if (argc != 3)
    {
        printf("ERROR : put 2 argument to use\n");
        exit(-1);
    }

    fd_copy = open(argv[1], O_RDONLY);
    if (fd_copy < 0)
    {
        printf("Error : no file %s\n", argv[1]);
        exit(-1);
    }

    fd_paste = open(argv[2], O_RDWR | O_CREAT | O_EXCL, paste_mode);
    if (fd_paste < 0)
    {
        printf("Can't create %s file with errorno %d\n", argv[2], errno);
        exit(-1);
    }

    while (1)
    {
        read_size = read(fd_copy, buf, MAX_BUF);
        if (read_size == 0)
            break;
        write(fd_paste, buf, read_size);
    }

    close(fd_copy);
    close(fd_paste);
    return 0;
}

char *flip_Str(char *str)
{

    int count = 0;
    int i = 0;
    char temp;

    while (str[i++] > 0)
    {
        count++;
    }

    for (i = 0; i < count / 2; i++)
    {
        temp = str[i];
        str[i] = str[count - i - 1];
        str[count - i - 1] = temp;
    }

    return str;
}
