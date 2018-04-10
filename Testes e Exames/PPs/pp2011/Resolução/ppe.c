/* ppe.c
e) Desenvolva um novo programa que, além de fazer o que é
pedido nas alíneas anteriores, cria um thread de verificação, i.e. que
executa a função checker() declarada em util.h. O argumento
desta função deve ser um apontador para uma variável do tipo
chkr_arg_t definida também em util.h, e aqui reproduzida:

typedef struct {
    int argc;          // to be initialized with argc of main()
    char **argv;       // to be initializedwith argv of main()
    vector_t *pvector; // to be initialized with pointer to the shared structure
} chkr_arg_t;

O thread de verificação deve ser criado antes dos threads de
inicialização e esperado pelo thread principal apenas depois daqueles
terem terminado.  

*Nota:* aqui também ainda devem ser patentes
os erros de competição, mesmo para um vector partilhado com um nº de
elementos relativamente pequeno, pois ainda pois não houve esforço de
sincronização no acesso ao vector!

Exemplo de invocação:
     ./ppe 6000 4000
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
vector.array = (int*)malloc(vector.len*sizeof(int*));
vector.next = 0;
vector.cnt[0] = vector.cnt[1] = 0;

pthread_mutex_init(&vector.lock, NULL);

pthread_create(&tchecker, NULL, checker, (void*)&ac);

for(int i=0; i<NT; i++){
    arg[i].X = i;
    arg[i].Y = n[i]*1000;
    arg[i].Z = &vector;
    pthread_create(&thread[i], NULL, print_vec, &arg[i]);
}
for(int i=0; i<NT; i++){
    pthread_join(thread[i], NULL);
}

pthread_join(tchecker, NULL);


print_vector(&vector);
free(vector.array);
pthread_mutex_destroy(&vector.lock);

printf("Main thread exiting\n");

return 0;
}
