# Aula 1

## Enunciados

### Ex 1
Escreva o programa fibonacci que calcula e apresenta na consola os primeiros 10 números da série de Fibonacci.

**Dica:** A série de Fibonnacci é uma série cujos 2 primeiros números têm valor 0 e 1, respectivamente, e os restantes são a soma dos 2 números que os precedem na série.

### Ex 2
O programa em input.c, apresentado na aula teórica, usa a função scanf() da biblioteca de C para ler um inteiro.
 a) Execute-o mas, em vez de digitar um nº inteiro como pedido, digite p.ex.  uma palavra. Qual o resultado?
 b) Altere o programa para i) validar o valor entrado e ii) ou apresentar esse valor ou então apresentar uma mensagem de erro.
 **Dica:** Leia o manual da função scanf(): man 3 scanf.

### Ex 3

Neste exercício pretende-se que use o operador sizeof da linguagem C para determinar o tamanho ocupado em memória por variáveis ou constantes de diferentes tipos.
 a) Escreva um programa que determina o tamanho de variáveis com os seguintes tipos básicos: char, short int, int, long int, float, double, void *.
 b) Escreva uma nova versão do mesmo programa que apresente o tamanho das variáveis declaradas no segmento de código seguinte:
int a[10];
struct complex {
    double re, im;
} z;
char *hello = "Hello, World!";
Procure explicar os valores apresentados.
 c) Assumindo as declarações da alínea anterior, quais deverão ser os valores retornados por:
sizeof(a[10])
sizeof(*hello)
Verifique se a sua resposta está correcta. Procure explicar os valores que obteve executando o seu programa.

### Ex 4
Neste exercício pretende-se ilustrar o uso de apontadores para transferir dados duma função para a função que a invoca.
 a) Escreva a função:
void in_fibonacci(int *fib, int n) 
a qual preenche a região de memória que lhe é passada no primeiro argumento com os n primeiros elementos da série de Fibonacci.
 b) Escreva a função main() a qual deverá invocar a função in_fibonacci() e após os seu retorno imprimir na consola os valores preenchidos por in_fibonacci().
IMP.- A região de memória passada a in_fibonacci() deverá ter o espaço necessário para armazenar n inteiros. Duas possibilidades são: 1) usar alocação estática declarando um vector com pelo menos n inteiros; 2) usar alocação dinâmica de memória, i.e. usar a função malloc().

### Ex 5

Inteiros que ocupam mais do que um byte podem ser armazenados de 2 formas na memória: 1) o byte mais significativo (MSB) pode ser armazenado primeiro, i.e. na posição de memória com endereço mais baixo, e depois os restantes por ordem sendo o byte menos significativo (LSB) armazenado na posição de memória com um maior endereço; 2) inversamente, o LSB é armazenado na posição de memória com menor endereço e o MSB na posição de memória com maior endereço. A primeira forma é designada por big endian enquanto a segunda por little endian.
A endianness é uma característica da arquitectura do processador. (Embora alguns processadores suportem as duas formas.)


Escreva o programa endian que lhe permita determinar a endianness da arquitectura IA32, usando apontadores para carácteres para aceder ao valor de cada um dos seus bytes separadamente.

Dica- Para imprimir o valor dum byte (carácter) em hexadecimal pode usar printf() com a string de formatação %#x.

### Ex 6

Escreva uma nova versão do programa anterior de forma a que em vez de imprimir o conteúdo de cada byte do inteiro em hexadecimal o imprima em binário.
Dica- Escreva uma função que imprime na consola os bits que compõem um carácter.
