#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void main(int argc, char *argv[]){
    int soma = 0, flag;
    char buffer[64];
    int fd = open (argv[1], O_RDONLY); //ficheiro n3
    int f1 = open (argv[2], O_RDONLY);
    if (f1 == -1) {
        f1 = open (argv[2], O_CREAT | O_WRONLY, S_IRWXU); //ficheiro n4        
    } else {
        printf("Ficheiro Existente.\n");
        close(fd);
        close(f1);
        return;
    }
    
    while((flag=read(fd, buffer, 64))!=0){
        soma = flag + soma;
        write(f1, buffer, flag);
    }
    printf("%d \n", soma);
    printf("%d \n", f1);
   
    close(fd);
    close(f1);
}