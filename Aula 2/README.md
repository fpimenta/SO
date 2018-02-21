## Questões

1. Os sistemas operativos (SO) são frequentemente apresentados quer como uma **máquina virtual** quer como uma **gestor de recursos**. Explique cada uma destas facetas dum SO.
2. Uma das abstracções suportadas por um SO é o de processo. Diga o que é um processo? Descreva dois serviços dum SO relacionados com a gestão de processos.
3. Sobre chamadas ao sistema
    1. O que é uma chamada ao sistema?
    2. Porque razão a implementação duma chamada ao sistema exige instruções não necessárias na implementação de funções?
    3. No entanto, do ponto de vista sintático, para um programador, uma chamada ao sistema parece ser uma função. Porquê?


## Problemas

**IMP.** Os seus programas deverão usar as **chamadas ao sistema** para acesso a ficheiros e **não** as funções de 
manipulação de _streams_ da biblioteca C.

### Ex 1
    
   Considere a cópia de um ficheiro.
    
   1. Escreva um programa que faz a cópia do ficheiro cujo nome lhe é passado como primeiro argumento 
    para a saída _standard_, à semelhança do utilitário cat quando invocado com um único argumento.No final 
    o seu programa deverá imprimir o comprimento total do ficheiro. (Confirme o resultado usando o comando wc -c.) 
    
   **IMP** Para garantir que a chamada ao sistema read tem que ser invocada múltiplas vezes 
    use _buffers_ de tamanho reduzido, p.ex. 256 bytes, e teste os seus programas com o código C respectivo. 
    
   2. Escreva uma versão do programa da alínea anterior tal que copia o ficheiro cujo nome lhe é passado 
    como primeiro argumento para um ficheiro cujo nome lhe é passado com segundo argumento.
    
   **IMP.** O seu programa deverá assinalar erro se o segundo argumento for o nome dum ficheiro que já existe. 
    Confirme o resultado do seu programa usando o comando diff. 
    
    
**Sugestão** Leia [as Secções 2.1 e 2.3 das notas do Prof. Pimenta Monteiro sobre ficheiros](http://web.fe.up.pt/~pfs/aulas/old/so2001/ap/cap2.pdf), bem como as _man pages_ das chamadas ao sistema nelas descritas. 

### Ex 2

O utilitário split parte um ficheiro em múltiplos ficheiros (para mais pormenores consulte a sua _man page_).
Escreva o programa merge o qual reconstrói um ficheiro a partir dos ficheiros gerados por split. 
Assume-se que estes ficheiros se encontram no directório onde merge é invocado. 
merge deve ser invocado da seguinte maneira: 

       merge <prefix>
 Onde `<prefix>` é o prefixo usado como argumento de split. O nome do ficheiro criado por merge deverá ser 
<prefix>mrg. 


**Sugestão**: Use as funções de manipulação de _strings_ da biblioteca C (man 3 string). 

### Ex 3

Considere as seguintes declarações:

```c
typedef char nome[30];
typedef struct {
        nome al;
        int notas[3];
} teste_t;
``` 

   1. Escreva um programa que crie um ficheiro “binário” que armazene registos do tipo teste_t, i.e. as classificações 
   num teste com 3 perguntas. Os campos de cada registo deverão ser perguntados ao utilizador.
   O seu programa deverá tomar como argumento o nome do ficheiro, o qual já pode existir.
   2. Escreva um programa que leia um ficheiro criado pelo programa da alínea anterior, e escreva na saída 
   os valores dos campos de cada registo, um registo por linha.
    

### Ex 4

Escreva o programa sample o qual “amostra” um ficheiro.Este programa deve ser invocado da seguinte forma: 

    ` sample <filename> <offset>`
onde 

<filename> é o nome do ficheiro a amostrar;  

<offset> é o deslocamento em relação ao princípio do ficheiro da amostra. 
O tamanho da amostra deve ser igual a um décimo do comprimento do ficheiro amostrado, 
a menos que o deslocamento especificado determine um valor inferior. A amostra deve ser escrita num ficheiro cujo nome é 
<filename>.smpl. 


**Sugestão** Para determinar o tamanho do ficheiro poderá usar uma das chamadas ao sistema stat(), fstat() ou lstat(). 
Leia a sua _man page_ bem como as [páginas 13 e 14 da Secção 2.5 das notas do Prof. Pimenta Monteiro 
sobre ficheiros](http://web.fe.up.pt/~pfs/aulas/old/so2001/ap/cap2.pdf) 


**Sugestão** Para avançar o _cursor_ do ficheiro poderá usar a chamada ao sistema lseek. 
Leia a sua _man page_ bem como a [sua descrição na Secção 2.3 das notas do Prof. Pimenta Monteiro sobre ficheiros](http://web.fe.up.pt/~pfs/aulas/old/so2001/ap/cap2.pdf) 

### Ex 5

Considere o problema 1, acima. Escreva uma nova versão a qual deverá comportar-se como descrito ou em a. ou em b.
desse problema, dependendo do número de argumentos da linha de comando.
**IMPORTANTE** A sua solução tem que usar a chamada ao sistema dup2(). 

Leia a sua _man page_ bem como a [Secção 2.1 das notas do Prof. Pimenta Monteiro sobre ficheiros](http://web.fe.up.pt/~pfs/aulas/old/so2001/ap/cap2.pdf)
