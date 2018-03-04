#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i = 0;
int j = 0;
int my_strlen(char *str){
    char c = str[j];
    while (c!= '\0'){
     i++;
     j++;
     c = str[j];
    }
    return i;
}

int main(int argc, char *argv[]){
    char *str;
    if(argc==2){
        str = argv[1];
    }
    printf("my_strlen - %d; strlen - %li\n", my_strlen(str), strlen(str));
}
