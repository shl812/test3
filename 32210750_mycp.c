/**
 * mycp.c	:copy files
 * @author	:Seeun Kim
 * @email	:rlaserma1014@dankook.ac.kr
 * @version	:1.0
 * @date	:2022.10.31
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 64

void copyFile(char *rd, char *wr);
void copyDir(char *rd, char *wr);

int main(int argc, char *argv[]){

	if((argc < 3) || (argc > 4)){
		printf("USAGE: %s input_file_name input_copy_file_name\n", argv[0]);
		printf("Or %s \"-r\" input_directory_name input_copy_directory_name\n", argv[0]);
		exit(-1);
	}

	//copy file
	if(argc == 3){
		copyFile(argv[1], argv[2]);
	}
	
	//copy directory
	else if(argc == 4){
		if(strcmp(argv[1], "-r") != 0){
			printf("Usage: %s -r input_directory_name input_copy_directory_name\n", argv[0]);
			exit(-1);
		}

		copyDir(argv[2], argv[3]);
	}

}

void copyFile(char *rd, char *wr){
	int fd, cpfd, read_size, write_size;
	struct stat st;
	char buf[MAX_BUF];

	fd = open(rd, O_RDONLY);

	if(fd < 0){
		printf("Can't open %s file with errno %d\n", rd, errno);
		exit(-1);
	}

	fstat(fd, &st);
	char filename[] = __FILE__;
	char *fn  = strtok(filename, ".");

	if(!S_ISREG(st.st_mode)){
		printf("Usage: ./%s -r input_directory_name input_copy_directory_name\n", filename);
		exit(-1);
	}

	cpfd = open(wr, O_WRONLY | O_CREAT | O_EXCL, st.st_mode);
	
	if(cpfd < 0){
		printf("Can't create %s file with errno %d\n", wr, errno);
		exit(-1);
	}

	while(1){
		read_size = read(fd, buf, MAX_BUF);
		if(read_size == 0)
			break;
		write_size = write(cpfd, buf, read_size);
	}

	close(fd);
	close(cpfd);
}

void copyDir(char *rd, char *wr){
	DIR *rddir, *wrdir;
	struct stat st;
	struct dirent *rdfile, *wrfile = NULL;

	int dd = access(rd, 0);
	
	if(dd < 0){
		printf("Can't find directory with errno %d\n", errno);
		exit(-1);
	}

	rddir = opendir(rd);
		
	stat(rd, &st);

	if(mkdir(wr, st.st_mode) < 0){
		printf("Can't create directory with errno %d\n", errno);
		exit(-1);
	}

	wrdir = opendir(wr);

	while((rdfile = readdir(rddir)) != NULL){

		if(rdfile->d_name[0] == '.')
			continue;

		//if directory
		if(rdfile->d_type == DT_DIR){
			stat(rdfile->d_name, &st);

			char read_dir[50];
			read_dir[0] = '\0';

			strcat(read_dir,"./");
			strcat(read_dir, rd);
			strcat(read_dir, "/");
			strcat(read_dir,rdfile->d_name);

			char write_dir[50];
			write_dir[0] = '\0';

			strcat(write_dir, "./");
			strcat(write_dir, wr);
			strcat(write_dir, "/");
			strcat(write_dir, rdfile->d_name);
			
			if(opendir(read_dir)){
				copyDir(read_dir, write_dir);
			}
			else{
				copyFile(read_dir,write_dir);
			}
		}

		//if file
		else if(rdfile->d_type == DT_REG){
			char read_dir[50];
			read_dir[0] = '\0';

			strcat(read_dir,"./");
			strcat(read_dir, rd);
			strcat(read_dir, "/");
			strcat(read_dir,rdfile->d_name);

			char write_dir[50];
			write_dir[0] = '\0';

			strcat(write_dir, "./");
			strcat(write_dir, wr);
			strcat(write_dir, "/");
			strcat(write_dir, rdfile->d_name);
			
			copyFile(read_dir, write_dir);
		}
		
	}

	closedir(rddir);
	closedir(wrdir);

}
