#include <stdio.h>

int main() {
    int atual=1;
    int ant=0;
    int i;
    
    printf("FIBONNACI SEQUENCE:\n");
    for(i=0;i<10;i++){
        printf("%i\n", ant); 
        atual=ant+atual;
        ant = atual - ant;
    }

}
