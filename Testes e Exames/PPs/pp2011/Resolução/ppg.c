/* ppg.c

g) Desenvolva um novo programa que garanta que, em qualquer
instante da inicialização do vector partilhado, a diferença máxima (em
milhares) entre o nº de elementos inicializado por cada thread não
excede um dado valor. Isto permitirá um maior grau de "entremeação" -
e competição - na execução dos threads. Tal diferença máxima de
elementos inicializados será apresentada como um parâmetro adicional
na linha de comando. Por ex., com uma invocação na forma :

   ./ppg 5000 5000 1

o seu programa deverá criar 2 threads, o primeiro dos quais deverá
inicializar 5000 milhares de elementos com o valor 0 e o segundo com
5000 milhares com o valor 1, sendo que em qualquer instante o nº de
elementos inicializado por cada thread não pode diferir em mais de
1000.

O seu programa deverá usar semáforos ou variáveis de condição para
sincronizar correctamente os 2 threads de inicialização sem "busy
waiting."

Nota: Assuma que o programa é invocado sempre com argumentos
cujos valores são tais que o valor absoluto da diferença dos 2
primeiros argumentos não excede o valor do 3º argumento.

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
pthread_cond_t cond;
int max_dif;
// a preencher com o seu código!

void *print_vec(void *arg){
	printf("Thread %lu running\n", pthread_self());

    arg_t *thrd = (arg_t *)arg;

    for (int i = 0; i < thrd->Y; i++){

        //LOCK
        assert(pthread_mutex_lock(&thrd->Z->lock) == 0);

        while(vector.cnt[thrd->X] - vector.cnt[!thrd->X] > max_dif)
            assert(pthread_cond_wait(&cond, &thrd->Z->lock) == 0);

		vector.array[vector.next++] = thrd->X;
        vector.cnt[thrd->X]++;

        pthread_cond_signal(&cond);

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

assert(argc == 4);
int n[NT];
pthread_t thread[NT], tchecker;
arg_t arg[NT];

// lidar com argumentos
if(!parse_int(argv[1], &n[0], 1) || !parse_int(argv[2], &n[1], 2) || !parse_int(argv[3], &max_dif, 3))
    perror("invalid arguments");

max_dif *= 1000;

ac.argc = argc;
ac.argv = argv;
ac.vector = &vector;

// inicializar estrutura vector_t
vector.len = n[0]*1000 + n[1]*1000;    
vector.array = (int*)malloc(vector.len*sizeof(int));
vector.next = 0;
vector.cnt[0] = vector.cnt[1] = 0;

assert(pthread_mutex_init(&vector.lock, NULL) == 0);
assert(pthread_cond_init(&cond, NULL) == 0);

print_vector(&vector);

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


free(vector.array);
assert(pthread_mutex_destroy(&vector.lock) == 0);
assert(pthread_cond_destroy(&cond) == 0);

printf("Main thread exiting\n");

return 0;
}