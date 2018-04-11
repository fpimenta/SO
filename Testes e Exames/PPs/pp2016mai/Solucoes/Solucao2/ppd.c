#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

long long du(int fd);
sem_t sem;

struct thread_info {
    pthread_t tid;
    char *file_name;
    long long file_size;
};

static void * thrfunc(void *arg){
    pthread_detach(pthread_self());
    struct thread_info *th_ag_r = (struct thread_info *) arg;
    int file_des = open(th_ag_r->file_name, O_RDWR);
    th_ag_r->file_size = du(file_des);
    
    sem_post(&sem);
    return NULL;
}

int main(){
    struct thread_info *th_ag = (struct thread_info *) malloc(sizeof(struct thread_info));
    int n_threads = 0;
    sem_init(&sem, 0, 0);
    
    while (scanf("%ms", &th_ag[n_threads].file_name) == 1){
        n_threads++;
        th_ag = (struct thread_info *) realloc(th_ag, sizeof(struct thread_info)*(n_threads+1));
    }
    
    for (int i =0; i < n_threads; i++)
        pthread_create(&th_ag[i].tid, NULL, thrfunc, (void *)&th_ag[i]);
    
    for (int i=0; i < n_threads; i++)
        sem_wait(&sem);
    
    for (int i = 0; i < n_threads; i++)
        printf("%s:\t%lld bytes\n", th_ag[i].file_name, th_ag[i].file_size);
}