#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>


int print_arg(int file, int size, char* args[]) {
    //Print Arguments
    
    char arg[] = " * Arguments: \n";
    int i, n;
    
    n = write(file, arg, strlen(arg));
    for(i=0; i < size; i++) {
        if((n = write(file, args[i], strlen(args[i])))== -1) {
            perror("ARGV ");
            return -1;
        }
        if((n = write(file,"\n", 1)) == -1) {
            perror("<newline> ");
            return -1;
        }
    }
    return 0;
}
 
int print_envp(int file,char* envar[]) {
    //Print Environment Variables
    
    char var[] = " * Environment Variables: \n";
    int i, n;
    
    n = write(file, var, strlen(var));
    for(i=0; envar[i] != NULL; i++) {
       if((n = write(file, envar[i], strlen(envar[i])))== -1) {
            perror("ARGV ");
            return -1;
       }
       if((n = write(file,"\n", 1)) == -1) {
            perror("<newline> ");
            return -1;
       }
    }
    return 0;
}


int main(int argc, char* argv[], char* envp[]) {
    int fd, w, status;
    pid_t pid;
    
    
    if(argc < 3) {
        printf("Error: Missing Argument!\n");
        _exit(1);
    }    
    
    if((pid = fork()) == 0) { // **CHILD**
        fd = open(argv[2], O_WRONLY); //Only prints, file needs to be already created
        if(fd < 0) {
            perror("OPEN Child");
            _exit(2);
        }
        
        if(print_arg(fd, argc, argv) == -1)
            _exit(3);
        
        //Print <newline>
        if((w = write(fd,"\n*Child*\n\n", strlen("\n*Child*\n\n"))) == -1) {
            perror("<newlines> ");
            _exit(3);
        }
            
        if(print_envp(fd, envp) == -1) 
            _exit(3);
    }
    else if(pid > 0) {  // ##Parent##
        
        waitpid(0, &status, 0);                        //Parent waits for the child to terminate. 
        if((status>>8) == 2 || (status>>8 == 3))       //If child has error, all processes terminate.
            exit(4);
        
        fd = open(argv[1], O_WRONLY);
        if(fd < 0) {
            perror("OPEN Parent");
            _exit(2);
        }
        
        if(print_arg(fd, argc, argv) == -1)
            _exit(3);
        
        //Print <newline>
        if((w = write(fd,"\n#PARENT#\n\n", strlen("\n#PARENT#\n\n"))) == -1) {
            perror("<newlines> ");
            _exit(3);
        }
        
        if(print_envp(fd, envp) == -1) 
            _exit(3);
    }
    else {  // Fork Error
        perror("Fork ");
        _exit(2);
    }
}
