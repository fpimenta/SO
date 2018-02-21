#include<stdio.h>
int main(){
    int a[10];
    
    struct complex {
        double re, im;
    } z;
    
    char *hello = "Hello, World!";
    printf("b:\n");
    printf("sizeof(a[10]):%ld\nsizeof(complex):%ld\nsizeof(hello):%ld\n", sizeof(a),sizeof(z), sizeof(hello));
    printf("%p\n",&hello);
}
