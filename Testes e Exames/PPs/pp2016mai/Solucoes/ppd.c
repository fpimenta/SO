#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>

long long du(int fd);

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int done = 0;

typedef struct X{
    char *file;
    long long int size;
} X;    

void *thrfunc(void * arg){
    X *dat = arg;
    int f;
    
    
    if( (f = open(dat->file,O_RDONLY)) != -1 ){
        dat->size = du(f);
    }
    
    
    pthread_mutex_lock(&mut);
    done++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mut);
    pthread_exit(NULL);
} 

int main(){
    
   
    X * data;
    data = (X *) malloc(sizeof(X)*10);
    char buf[255];
    register int nfiles = 0, space = 10;
    
   
    while(scanf(" %s", buf ) == 1){
            data[nfiles].file = (char*)malloc(sizeof(char*)*255);
            strcpy(data[nfiles].file, buf);
            nfiles++;space--;
            if( space == 1){
                   data = (X*) realloc(data,sizeof(data)+sizeof(X)*10);
                   space = 10;
            }    
    }   
    pthread_t idT[nfiles];
    for(int i = 0; i < nfiles;i++){
      pthread_create(&idT[i],NULL,thrfunc,&data[i]);  
    }   
    
    pthread_mutex_lock(&mut);
    while( done < nfiles){
     pthread_cond_wait(&cond,&mut);
    }
    pthread_mutex_unlock(&mut);
    for(int i = 0; i < nfiles; i++){
        printf("%s:\t%lld bytes\n",data[i].file,data[i].size);
    }    
    
    exit(EXIT_SUCCESS);
}    
