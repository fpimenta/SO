/* ppb.c
 *  The Hungry Birds Problem - pass arguments to threads and receive values from them when they finish!

Program invocation:
	./ppb <n. babybirds> <n. food portions> <n. refills>

Invocation example:
     ./ppb 3 5 10000
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define MAXBABIES 100

int finish = 0;	// termination of simulation (flagged by parent bird)
int foodbits = 0;	// is the current number of bits of food in the "food-teat"

struct checkerarg {	// conveys info to checker
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
	int *eating;	// ptr to number of babies that are eating at a time
	pthread_mutex_t *mut; // for overall concurrency control to shared data
};
struct parentarg {	// conveys info to parent bird
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
};
struct babyarg {	// conveys info to baby birds
	int id;	// baby identification
	int *eating;	// ptr to number of babies that are eating at a time
};

void *checker(void *);	// checker thread
void *parent(void *);	// parent thread
void *baby(void *);	// baby thread


int main(int argc, char *argv[]) {

setbuf(stdout, NULL);
	int B;	// number of babies
	int F;	// number of bits of food of each refill
	long R;	// number of refills - parent bird can then retire!
	int working = 0;	// represents the binary state of parent bird:
	int eating = 0;	// number of babies that are eating at a time
	struct parentarg pa;	// conveys info to parent bird (and checker!)
	struct checkerarg ca;	// conveys info to parent bird (and checker!)
	struct babyarg ba[MAXBABIES];	// conveys baby identification
	pthread_t tchecker, tparent, tbaby[MAXBABIES];

if( argc != 4) {
	printf("Program invoked with wrong number of arguments.\n");
	printf("Program usage: %s <n. babybirds> <n. food portions> <n. refills>\n", argv[0]);
	exit(-1);
    }
else {
	B = atoi(argv[1]);
	F = atoi(argv[2]);
	R = atoi(argv[3]);
	}
printf("\nSimulation started\n");

ca.f = F;
ca.r = R;
ca.working = &working;
ca.eating = &eating;
ca.mut = NULL;

pthread_create(&tchecker, NULL, checker, &ca);


pa.f = F;
pa.r = R;
pa.working = &working;

pthread_create(&tparent, NULL, parent, &pa);


for (int n_baby = 0; n_baby < B; n_baby++){
    ba[n_baby].id = n_baby;
    ba[n_baby].eating = &eating;
    pthread_create(&tbaby[n_baby], NULL, baby, &ba[n_baby]);
}

pthread_join(tparent, NULL);

long *pbits_eaten[B];	// get baby bird's eating statistics
for (int n_baby = 0; n_baby < B; n_baby++){
    pthread_join(tbaby[n_baby], (void *)&pbits_eaten[n_baby]);
    printf ("\nNumber of bits of food eaten by baby %d / total of bits: %ld / %ld ", n_baby, *pbits_eaten[n_baby], F*R);
}

printf("\nSimulation finished\n");

exit (0);
} // main()


void *parent(void *arg) {	// parent bird thread
    struct parentarg pa;
    
    pa = *((struct parentarg*) arg);
    printf ("\n\tParent starting");
    printf ("\n\tParent received args f (%d), r (%ld), working (%d)", pa.f , pa.r , *(pa.working));
    printf ("\n\tParent finishing");
    
    return NULL;
} // parent()


void *baby(void *arg){	// baby thread
    struct babyarg ba;
    long *food_baby = (long *) malloc(sizeof(long));
    (*food_baby) = 0;
    
    ba = *((struct babyarg*) arg);
    printf ("\n   Baby bird %d beginning",ba.id);
    printf ("\n   Baby received args id (%d), eating (%d)", ba.id , *(ba.eating));

    printf ("\n   Baby bird %d finishing", ba.id);
    
    return (food_baby);
} // baby()
