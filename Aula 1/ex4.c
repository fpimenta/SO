#include <stdio.h>
#include <stdlib.h>
void in_fibonacci(int *fib, int n){
    fib[0] = 0;
    fib[1] = 1;
    for(int i=2;i < n;i++) fib[i]=fib[i-1]+fib[i-2];
}

int main(int argc, char *argv[]){
    int n;
    int *fib;
    if(argc != 2){
        printf("Insira o valor de n:");
        scanf("%d", &n);}
    else n = strtol(argv[1],NULL,0);
    fib = malloc(n*sizeof(int));
    in_fibonacci(fib, n);
    printf("\nOUTPUT:\n");
    for(int i = 0; i<n; i++) printf("%d\n", fib[i]);
}
