
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

long long du(int fd);

struct thread_info {
    pthread_t tid;
    char *file_name;
    long long file_size;
};

static void * thrfunc(void *arg){
    struct thread_info *th_ag_r = (struct thread_info *) arg;
    int file_des = open(th_ag_r->file_name, O_RDWR);
    th_ag_r->file_size = du(file_des);
    return NULL;
}

int main(){
    struct thread_info th_ag;
    scanf("%ms ", &th_ag.file_name);
    pthread_create(&th_ag.tid, NULL, thrfunc, (void *)&th_ag);
    pthread_join(th_ag.tid, NULL);
    printf("%s:\t%lld bytes\n", th_ag.file_name, th_ag.file_size);
}