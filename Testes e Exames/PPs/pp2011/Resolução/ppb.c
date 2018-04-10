/* ppb.c

b) Desenvolva um novo programa que, para além de fazer o
que é pedido em a) crie os 2 threads de inicialização. Cada
um destes threads deverá invocar a função printf() do seguinte
modo:

	printf ("Thread %d running\n", pthread_self());

O thread principal deverá esperar que cada um dos threads de inicialização
termine, após o que deverá imprimir:

	printf ("Main thread exiting\n");

Nota: Nesta alínea não precisa de passar qualquer argumento aos threads
de inicialização.

Exemplo de invocação:
     ./ppb 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

// a preencher com o seu código!

void *print_vec(void *arg){
	printf("Thread %d running\n", pthread_self());
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!

assert(argc == 3);
int n[NT];
pthread_t thread[NT];

// lidar com argumentos
if(!parse_int(argv[1], &n[0], 1) || !parse_int(argv[2], &n[1], 2))
    perror("invalid arguments");

// inicializar estrutura vector_t
vector.len = n[0]*1000 + n[1]*1000;    
vector.array = (int*)malloc(vector.len*sizeof(int*));
vector.next = 0;
vector.cnt[0] = vector.cnt[1] = 0;

pthread_mutex_init(&vector.lock, NULL);

pthread_create(&thread[0], NULL, print_vec, NULL);
pthread_create(&thread[0], NULL, print_vec, NULL);

pthread_join(thread[0], NULL);
pthread_join(thread[1], NULL);


print_vector(&vector);
free(vector.array);
pthread_mutex_destroy(&vector.lock);

printf("Main thread exiting\n");

return 0;
}

// a preencher com o seu código!
