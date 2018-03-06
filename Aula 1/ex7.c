#include <stdio.h>
#include <strings.h>

void main(){
    unsigned int x = 0x12345678; //1 byte -> 2 numeros -> 4 bytes no total
    char *c = (char *) &x; //1 char -> 1byte
    printf("O valor a por em memoria é: %#x\n",x); 
    printf("Os valores foram guardados da seguinte forma: %#x %#x %#x %#x\n", c[0], c[1], c[2], c[3]);
    if (c[0]==0x78){
        printf("Little Endian\n");
    }
    if (c[3]==0x78){
        printf("Big Endian\n");
    }
}