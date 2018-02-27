#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void main(int argc, char *argv[]){
    int soma = 0, flag;
    char buffer[64];
    int fd = open (argv[1], O_RDONLY);
    while((flag=read(fd, buffer, 64))!=0){
        soma = flag + soma;
        write(STDOUT_FILENO, buffer, flag);
    }
   printf("%d \n", soma);
   close(fd);
    
}