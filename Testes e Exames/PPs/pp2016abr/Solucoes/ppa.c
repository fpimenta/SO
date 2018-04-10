#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
int match_line(int fd, char *str);
void *pesquisa(void *arg);
char *str;
typedef struct {
    int fd;
    char *name;
} pesquisa_arg;


    
int main(int argc, char *argv[]){
    int i;
    str = argv[1];
    pthread_t tid;
  
    pesquisa_arg t_arg[argc-2];
    for (i=0; i<(argc-2); i++){
        t_arg[i].fd = open(argv[i+2], O_RDONLY);
        t_arg[i].name = argv[i+2];
        
    }
    
    pthread_create(&tid, NULL, pesquisa, &t_arg);
    pthread_join(tid, NULL);
    
}

void *pesquisa(void *arg){
    pesquisa_arg t_arg = *(pesquisa_arg *)arg;
    int line;
    while( (line = match_line(t_arg.fd, str)) != 0){
        if(line!=0)
            printf("%s:\t%d\n", t_arg.name, line);
    }
    return NULL;
        
}
