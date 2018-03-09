# Folha nº 4: POSIX Threads (1ª Parte)

## Questões
1. Considere a implementação com múltiplos *threads* dum servidor *Web* discutido na aula teórica. Em princípio, seria possível realizar uma implementação semelhante usando apenas processos. Qual é a principal vantagem de usar *threads* em vez de processos?
2. Nas transparências das aulas teórico-práticas escrevi:

    > "Grosso modo, enquanto que um processo corresponde à execução dum programa, um *thread* corresponde à execução duma função." 

    Explique esta afirmação à luz da API POSIX para *threads* e do ciclo de vida dum *thread* POSIX.
3. De acordo com o protótipo de ``pthread_create()`` o protótipo da função a executar pelo *thread* criado deverá ser:

    ``void *fun(void *arg)``

  * Por que razão quer o argumento quer o valor de retorno são do tipo ``void *`` e não, p.ex., ``int *``?
  * Como é possível obter o valor retornado pela função ``fun()`` executada pelo *thread* criado?
  * Explique por que razão um *thread* não deve retornar o endereço duma variável local automática declarada dentro de fun.
  * No caso de processos Unix/Linux, quando um processo termina, o valor por ele retornado pode ser recebido apenas pelo processo pai. A API POSIX (i.e. de ``libpthread``, impõe restrições semelhantes? 

## Problemas

**Nota:** Para compilar os seus programas baseados em *threads* deverá usar a opção ``-phtread`` do compilador. Isto garante a ligação com a biblioteca ``libpthread`` e com as funções apropriadas, i.e. *thread-safe*, da biblioteca C.

1. Escreva um programa cujo thread principal cria 3 novos threads. Cada thread (diferente do principal) deve escrever os seus pid e tid e terminar retornando um número inteiro entre 1 e 3 distinto do retornado pelos restantes threads. O thread principal deve escrever no terminal o seu pid e o valor retornado por cada um dos outros threads.
  * Qual a relação entre os pids dos diferentes threads dum programa? E os seus tids?
  * O que acontece se o thread principal não esperar pelos restantes? Teste. 
2. Escreva um nova versão do programa anterior na qual o número de novos threads a criar, n, é passado através da linha de comando. Cada thread (diferente do principal) deve escrever o    seu tid e terminar retornando um número inteiro entre 1 e n distinto do retornado pelos restantes threads.

    **Dica** Usa a função strtol para converter o argumento da linha de comando num inteiro.

    Teste o seu programa para diferentes valores de n.
3. Escreva um programa multi-threaded para inicializar um vector de inteiros.

    O seu programa deverá aceitar 2 argumentos de tipo inteiro: o número de elementos do vector e o número de threads que farão a sua inicialização, por esta ordem.

    O thread principal deverá processar os argumentos e criar os threads que fazem a inicialização do vector. Após a inicialização do vector, o thread principal deverá listar cada um dos elementos do vector.

    Cada um dos threads criados pelo thread principal deverá inicicializar a sua parte do vector. O elemento i do vector deverá ser inicializado com o inteiro i.

    **Dica** Identifique os dados que cada thread precisa para processar o seu sub-vector e defina uma estrutura de dados que o thread principal usará para passar esses dados como argumento aos restantes threads.
4. Se, no programa anterior, o número de elementos inicializados por qualquer thread diferir em mais de 1 da média, escreva uma nova versão onde tal não se verifique.

    Cada um dos threads deverá imprimir informação no stdout para ilustrar que funciona correctamente.

    **Dica** Use as operações divisão inteira e resto da divisão inteira. 