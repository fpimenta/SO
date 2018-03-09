#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADN 3

typedef struct X {
    int count;
    int tid[THREADN];
} X;


void *tfunc(void *arg){
    X *argR = arg;
    int countA = ++(*argR).count;
    
    printf("THREAD SELF - 0x%X\t PID - %d\n", (int) pthread_self(), (int) getpid());
    printf("COUNT: %d\n", countA);
    return NULL;
}

int main(){
    pthread_t idT[THREADN];
    X argT;
    argT.count = 0; 
    for (int i = 0; i < THREADN; i++)
        pthread_create(&idT[i], NULL, tfunc, &argT);

    for (int i = 0; i < THREADN; i++)
        pthread_join(idT[i], NULL);
    
    printf(" === MAIN ===\n");
    for (int i = 0; i < THREADN; i++){
        printf("Thread %d: 0x%X\n", i, (int) idT[i]);
    }
    
    return 0;
}