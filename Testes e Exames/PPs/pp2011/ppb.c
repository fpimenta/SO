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

vector_t vector;	// estrutura de dados a partilhar pelos threads

// a preencher com o seu código!

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!

print_vector(&vector);
return 0;
}

// a preencher com o seu código!
