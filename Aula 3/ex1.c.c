#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]) {
    int i=0;
    
    //Print Arguments
    for(i=0; i<argc; i++)
        printf("%s\n", argv[i]);
    
    //Print Environment Variables
    for(i=0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);

    //Codes to change Environment Variables
    //-[VariableName]=[Value]
    //-export [VariableName]
}