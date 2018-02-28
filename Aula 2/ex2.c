#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 64

int main(int argc, char *argv[]){
	int in_file, in_size, out_file, rbytes;
	char* in_name;
	char buff[64];
	if (argc != 2){
		printf("Error: Argument is missing!\n");
		exit(1);
	}
	out_file = open("mrg",O_WRONLY | O_CREAT | O_EXCL, 0644);
	if(out_file == -1 && errno == EEXIST){
		printf("Error: %s already exists!\n", argv[2]);
	}
	in_name = argv[1];
	in_size = strlen(in_name);
	strcat(in_name, "a");
	while(1){
		in_file = open(in_name,O_RDONLY);
		if(in_file == -1) break;
		while(1){
			rbytes = read(in_file, buff, BUF_SIZE);
			write(out_file, buff, rbytes);
			if(rbytes <= 0) break;
		}
		close(in_file);
		in_name[in_size] = in_name[in_size]+1;
	}
	close(out_file);
}
