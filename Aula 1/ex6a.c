#include <stdio.h>
void main(){
    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
      while(1){
        printf(" Month: %s\n", *months);
        if(**months== 'D'){
            break;
        }
        *months = *months + 4;
      
      }

}