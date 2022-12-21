/*
 * mycp.c       : cp command program
 * @author      : 허준
 * @email       : heojun990322@gmail.com
 * @version     : 1.0
 * @data        : 2022. 10. 28
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
        int fd_source, fd_target, read_size, write_size;
        char buf[MAX_BUF];
        struct stat st; // attributes data structure
        struct utimbuf time_attr; // time attributes data structure

        if (argc != 3) {
                printf("USAGE : %s [source file name] [target file name]", argv[0]);
                exit(-1);
        }

        fd_source = open(argv[1], O_RDONLY);
        if (fd_source < 0) {
                printf("Can't open %s file with errno %d\n", argv[1], errno);
                exit(-1);
        }

        if (stat(argv[1], &st) == -1) { // st has source file attributes
                printf("Can't access %s file attributes with errno %d\n", argv[1], errno);
                exit(-1);
        }

        // permission of target file is the same as source file
        fd_target = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, st.st_mode);
        if (fd_target < 0) {
                printf("Can't create %s file with errno %d\n", argv[2], errno);
                exit(-1);
        }

        while (1) { // data flow : source file -> buf -> target file
                read_size = read(fd_source, buf, MAX_BUF);
                if (read_size == 0)
                        break;
                write_size = write(fd_target, buf, read_size);
        }

        close(fd_source);
        close(fd_target);

        time_attr.actime = st.st_atime; // last access time of source
        time_attr.modtime = st.st_mtime; // last modify time of source
        utime(argv[2], &time_attr); // initialization time attributes of target

        return 0;
}
