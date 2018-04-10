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

vector_t vector;	// estrutura de dados a partilhar pelos threads
chkr_arg_t ac;	// estrutura de dados a usar no argumento para o thread de verificação

// a preencher com o seu código!

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!

print_vector(&vector);
return 0;
}

// a preencher com o seu código!
