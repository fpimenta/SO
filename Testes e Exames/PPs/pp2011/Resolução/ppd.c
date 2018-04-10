/* ppd.c

d) Desenvolva um novo programa que, para além de fazer o
que é pedido nas alíneas anteriores, faça com que os 2 threads de
inicialização inicializem *mesmo* o vector partilhado, mas sem
tentarem evitar erros de competição ("race conditions").  A impressão
da informação já pedida na alínea anterior irá permitir ver o trabalho
que foi efectuado.  

*Nota:* aqui já deve ser possível observar que há erros de
competição, mesmo para um vector partilhado com um nº de elementos
relativamente pequeno! É óbvio, pois não houve esforço de
sincronização no acesso ao vector!

Exemplo de invocação:
     ./ppd 6000 4000
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

// a preencher com o seu código!

void *print_vec(void *arg){
	printf("Thread %lu running\n", pthread_self());

    arg_t *thrd = (arg_t *)arg;
    printf("Thread %d: cnt = %d, vp = %p\n", thrd->X, thrd->Y, &thrd->Z);

    for (int i = 0; i < thrd->Y; i++, vector.cnt[thrd->X]++)
		vector.array[vector.next++] = thrd->X;

    print_vector(thrd->Z);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!

assert(argc == 3);
int n[NT];
pthread_t thread[NT];
arg_t arg[NT];

// lidar com argumentos
if(!parse_int(argv[1], &n[0], 1) || !parse_int(argv[2], &n[1], 2))
    perror("invalid arguments");

// inicializar estrutura vector_t
vector.len = n[0]*1000 + n[1]*1000;    
vector.array = (int*)malloc(vector.len*sizeof(int*));
vector.next = 0;
vector.cnt[0] = vector.cnt[1] = 0;

pthread_mutex_init(&vector.lock, NULL);

for(int i=0; i<NT; i++){
    arg[i].X = i;
    arg[i].Y = n[i]*1000;
    arg[i].Z = &vector;
    pthread_create(&thread[i], NULL, print_vec, &arg[i]);
}
for(int i=0; i<NT; i++){
    pthread_join(thread[i], NULL);
}


print_vector(&vector);
free(vector.array);
pthread_mutex_destroy(&vector.lock);

printf("Main thread exiting\n");

return 0;
}