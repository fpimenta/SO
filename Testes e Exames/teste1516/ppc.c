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

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;


    
int main(int argc, char *argv[]){
    int i;
    int N = argc-2;
    str = argv[1];
    pthread_t tid[N];
    pesquisa_arg t_arg[N];
    
    for (i=0; i<(N); i++){
        t_arg[i].fd = open(argv[i+2], O_RDONLY);
        t_arg[i].name = argv[i+2];
        
    }
    
    for (i=0; i<(N); i++){
       pthread_create(&tid[i], NULL, pesquisa, &t_arg[i]);
    }
    
    for (i=0; i<(N); i++){
      pthread_join(tid[i], NULL);
    }
    
    
}

void *pesquisa(void *arg){
    pesquisa_arg t_arg = *(pesquisa_arg *)arg;
    int line;
    pthread_mutex_lock(&mut);
    while( (line = match_line(t_arg.fd, str)) != 0){
        if(line!=0)
            printf("%s:\t%d\n", t_arg.name, line);
    }
    pthread_mutex_unlock(&mut);
    return NULL;
        
}