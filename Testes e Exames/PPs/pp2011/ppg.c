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
