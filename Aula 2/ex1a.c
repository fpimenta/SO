#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 64

int main(int argc,char* argv[]){
	int filedes, rbytes, totby;
	char buff[BUF_SIZE];
	totby = 0;
	
	if(argc!=2) printf("Error: Argument is missing!\n");
	filedes = open(argv[1],O_RDONLY);
	
	while(1){
		rbytes = read(filedes, buff, BUF_SIZE);
		write(STDOUT_FILENO, buff, rbytes);
		totby = totby + rbytes;
		if(rbytes <= 0) break;
	}
	printf("\n");
	close(filedes);
}
