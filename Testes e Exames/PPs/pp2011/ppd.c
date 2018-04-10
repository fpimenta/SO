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

vector_t vector;	// estrutura de dados a partilhar pelos threads

// a preencher com o seu código!

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!

print_vector(&vector);
return 0;
}

// a preencher com o seu código!
