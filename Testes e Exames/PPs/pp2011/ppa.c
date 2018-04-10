/* ppa.c
a) Escreva um programa que processe os argumentos da linha
de comando, inicialize a estrutura de tipo "vector_t" a usar e,
finalmente, mostre o estado do vector partilhado por via da invocação
da função "print_vector()" (incluída em util.c)

Exemplo de invocação:
     ./ppa 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>


vector_t vector;	// estrutura de dados a partilhar pelos threads

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!
assert(argc == 3);
int n[NT];


// lidar com argumentos
if(!parse_int(argv[1], &n[0], 1) || !parse_int(argv[2], &n[1], 2))
    perror("invalid arguments");

// inicializar estrutura vector_t
vector.len = n[0]*1000 + n[1]*1000;    
vector.array = (int*)malloc(vector.len*sizeof(int*));
vector.next = 0;
vector.cnt[0] = vector.cnt[1] = 0;

pthread_mutex_init(&vector.lock, NULL);
print_vector(&vector);
free(vector.array);
pthread_mutex_destroy(&vector.lock);

return 0;
}
