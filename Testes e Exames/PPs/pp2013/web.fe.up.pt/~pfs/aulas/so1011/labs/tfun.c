#include <stdio.h>

#define DEBUG 0

#define MAX_ITER	10000000

typedef struct {
    long *cnt;
    int id;
} targ_t;

void *tfun(void *arg) {

    targ_t *targ = (targ_t *) arg;
    int i;
  

    printf("Thread %d starting\n", targ->id);

    printf ("&cnt = %p \n", targ->cnt);

    for(i = 0; i < MAX_ITER ; i++) {
	if( DEBUG ) 
	    printf("b4:  %ld ", *(targ->cnt)); 
	(*(targ->cnt))++; 
	/* If cnt is always N*MAX_ITER 
	   Then comment the previous line and 
	   uncomment the following 3 lines 
	   aux = *(targ->cnt);
	   aux++;
	   *(targ->cnt) = aux; 
	   */
	if (DEBUG )
	    printf("\t %ld \n", *(targ->cnt)); 
    }
    printf("Thread %d done\n", targ->id);
    return NULL;
}

