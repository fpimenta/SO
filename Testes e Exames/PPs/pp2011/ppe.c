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

vector_t vector;  // estrutura de dados a partilhar pelos threads
chkr_arg_t ac;	  // estrutura de dados a usar no argumento para o thread de verificação

// a preencher com o seu código!

int main(int argc, char *argv[]) {
setbuf(stdout, NULL);

// a preencher com o seu código!

print_vector(&vector);
return 0;
}

// a preencher com o seu código!
