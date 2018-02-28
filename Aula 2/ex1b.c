#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 64

int main(int argc,char* argv[]){
	int sourcef, newf, rbytes, totby;
	char buff[BUF_SIZE];
	totby = 0;
	
	if(argc!=3){
		printf("Error: Arguments are missing!\nArguments: [SOURCE_FILE] [NEWFILE]\n");
		exit(1);
	}
	
	sourcef = open(argv[1],O_RDONLY);
	newf = open(argv[2],O_WRONLY | O_CREAT | O_EXCL, 0644);
	if(newf == -1 && errno == EEXIST){
		printf("Error: %s already exists!\n", argv[2]);
		exit(1);
	}
	
	while(1){
		rbytes = read(sourcef, buff, BUF_SIZE);
		write(newf, buff, rbytes);
		totby = totby + rbytes;
		if(rbytes <= 0) break;
	}
	printf("The file was successfully copied to %s.\n",argv[2]);
	close(sourcef);
	close(newf);
}
