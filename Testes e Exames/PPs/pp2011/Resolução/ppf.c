/* ppf.c

f) Desenvolva um novo programa, corrijindo a versão da
alínea e) por forma a que, garantidamente, não haja "race conditions",
mesmo para um vector partilhado com um elevado nº de elementos!

Exemplo de invocação:
     ./ppf 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>


typedef struct {
    int X;
    int Y;
    vector_t *Z;
} arg_t;

vector_t vector;	// estrutura de dados a partilhar pelos threads
chkr_arg_t ac;
// a preencher com o seu código!

void *print_vec(void *arg){
	printf("Thread %lu running\n", pthread_self());

    arg_t *thrd = (arg_t *)arg;

    for (int i = 0; i < thrd->Y; i++){

        //LOCK
        assert(pthread_mutex_lock(&thrd->Z->lock) == 0);

		vector.array[vector.next++] = thrd->X;
        vector.cnt[thrd->X]++;

        //UNLOCK
        assert(pthread_mutex_unlock(&thrd->Z->lock) == 0);
    };

    printf("Thread %d: cnt = %d, vp = %p\n", thrd->X, thrd->Y, thrd->Z->array);
    print_vector(thrd->Z);

	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!

assert(argc == 3);
int n[NT];
pthread_t thread[NT], tchecker;
arg_t arg[NT];

// lidar com argumentos
if(!parse_int(argv[1], &n[0], 1) || !parse_int(argv[2], &n[1], 2))
    perror("invalid arguments");

ac.argc = argc;
ac.argv = argv;
ac.vector = &vector;

// inicializar estrutura vector_t
vector.len = n[0]*1000 + n[1]*1000;    
vector.array = (int*)malloc(vector.len*sizeof(int));
vector.next = 0;
vector.cnt[0] = vector.cnt[1] = 0;

assert(pthread_mutex_init(&vector.lock, NULL) == 0);

assert(pthread_create(&tchecker, NULL, checker, (void*)&ac) == 0);

for(int i=0; i<NT; i++){
    arg[i].X = i;
    arg[i].Y = n[i]*1000;
    arg[i].Z = &vector;
    assert(pthread_create(&thread[i], NULL, print_vec, &arg[i]) == 0);
}
for(int i=0; i<NT; i++){
    assert(pthread_join(thread[i], NULL) == 0);
}

assert(pthread_join(tchecker, NULL) == 0);


print_vector(&vector);
free(vector.array);
assert(pthread_mutex_destroy(&vector.lock) == 0);

printf("Main thread exiting\n");

return 0;
}

