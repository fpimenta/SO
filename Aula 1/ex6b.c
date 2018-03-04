#include <stdio.h>
#include <strings.h>

int no_months(char *mon1, char *mon2){
    int aux, count=0;
    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char *copia = *months; 
    for(aux=0; aux<12; aux++){
        if (strncasecmp(mon1, *months, 3)==0){
           while(strncasecmp(mon2, *months, 3)!=0){
               count++;
                if((**months == 'D')){
                    *months = copia;
                }
                else{
                *months = *months + 4;
                }
           }
           return count;
        }
        else{
            if((**months == 'D')){
                    *months = copia;
            }
            else{
                *months = *months + 4;
            }
        }
            
    }    
}

void main(){
    char nom1[3];
    char nom2[3];
   printf("Insere 2 meses:\n");
   printf("Mes1:");
   scanf("%s", nom1);
   printf("Mes2:");
    scanf("%s", nom2);
    printf("%d meses\n", no_months(nom1, nom2));
}