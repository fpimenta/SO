#include <stdio.h>

void main(){

    int a[10];
    char *hello = "Hello, World!";
    struct complex {
        double re, im;
    } z;
    short s;
    long l;
    long long ll;

    printf("Int - %li; Char - %li; Short - %li; Long - %li; Long Long - %li \n", sizeof(int), sizeof(char), sizeof(short), sizeof(long), sizeof(long long));
    
    printf("A - %li; COMPLEX - %li; Hello - %li, A[0] - %li \n", sizeof(a), sizeof(z), sizeof(*hello), sizeof(a[0]));
    //a = 40 pq (int)4*10 ## Complex = 16 pq (double)8*2
    //Hello = 8 pq é endereço e *Hello = 1 pq é a 1etra (apontador)
    
}
