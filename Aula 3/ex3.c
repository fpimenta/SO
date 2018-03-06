#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

void main() {
    int status;
    pid_t pid;
    
    if((pid = fork()) < 0) { // Error
        perror("FORK");
        exit(1);
    }
    else if (pid > 0) {  // Parent
        wait(&status);
        printf("Ft - 'My PID is %d. My father PID is: %d.'\n", getpid(), getppid());
        printf("Child Exit Code - %d.\n", status>>8);
        _exit(12);
    }
    else {              // Child
        if((pid = fork()) < 0) { // Error
            perror("FORK");
            _exit(1);
        }
        else if(pid == 0){       // Grand_Child
            printf("Gc - 'My PID is %d. My father PID is: %d.'\n", getpid(), getppid()); 
            _exit(2);
        }
        else {                   // Child
            wait(&status);
            printf("Ch - 'My PID is %d. My father PID is: %d. My Child PID %d.'\n", getpid(), getppid(), pid); 
            printf("GrandChild Exit Code - %d.\n", status>>8);
            _exit(3);
        }
    }
}
