/* ppc.c

c) Desenvolva um novo programa, que além de fazer o que é pedido
nas alíneas anteriores, deverá fazer com que cada um dos threads
de inicialização invoque a função printf() do seguinte modo:

	printf ("Thread %d: cnt = %d, vp = %p\n", X, Y, Z);

onde X representa o identificador do thread (ou 0 ou 1), Y representa
o nº de elementos que o thread deverá inicializar, e Z o endereço da
estrutura de dados do tipo vector_t partilhada pelos threads de
inicialização.  Antes de terminar cada thread deverá ainda
invocar a função print_vector() já referida.

Nota: Cada thread deverá invocar esta instrução com um valor X diferente.

Exemplo de invocação:
     ./ppc 6000 4000
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
