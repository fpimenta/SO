#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//Codigo usado quando o slipt é feito da seguinte forma "split -d -b [tamanho desejado] [nome do ficheiro] [prefixo desejado]". -d -> permite separar os ficheiros colocando sufixos numericos; -b permite escolher o tamanho de cada ficheiro

void main(int argc, char* argv[]) {

    char mrg[6]="merge",str[100], buffer[64];
    int n, i;  // n - nr de bytes lidos; i - var. aux
    int fd, fl; //fd - ficheiro destino, fl - ficheiro de leitura
    
    
        if(argc != 3) {
            printf("Não é possivel executar programa!\n");
            exit(1);
        }
        
        if ((strcpy (str,argv[2]) != 0))            
            if((strcat(str, ".mrg") == 0))
                exit(2);
        
        // printf("%s\n",str); 
        
        fd = open(str, O_CREAT | O_WRONLY, S_IRWXU); //Criar ficheiro
        if(strcmp(argv[1],mrg) == 0) {
            for(i=0; i<1000; i++) {                   //Ciclo "infinito" que pára quando deixa de haver ficheiros  
                sprintf(str, "%s%d%d", argv[2],0,i);
                //printf("%s \n", str);
                fl = open(str, O_RDONLY);
                if (fl == -1)                       //Nao ha mais ficheiros para ler
                    break;
                while((n=read(fl, buffer, 64)) != 0){
                    write(fd, buffer, n);
                }
                close(fl);
            }                                       
        }
	close(fl);
        close(fd);
}
