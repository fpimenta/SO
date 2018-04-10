#include <sys/times.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>

#define DEBUG 0

#define BUF_SIZE	100000
#define ITER		10000000

#define PROD_THRD	3
#define CONS_THRD	3

#define USAGE_STRING	"Usage: %s\n"

extern int errno;

/* This is the bounded buffer type */
typedef struct {
    int cnt, in, out;
    pthread_mutex_t lock;		/* Mutex to avoid race conditions */
    int buf[BUF_SIZE];		/* The data passed is the id of the
				 *  producer */
} bbuf_t;

/* This is the type of the arguments passed to each producer:
 *  because we want each consumer to keep track of the producer
 *  of the items it consumes, it is easier to assign each producer
 *  an id between 0 and PROD_THRD-1 */
typedef struct {
    bbuf_t *bbp;
    int 	 id;
} parg_t;

/* 
 * yield()
 * Because there is no yield system call in Linux, what we
 * do is to put the thread to sleep for 1 ms. Actually, it 
 * will sleep for at least 1/HZ, which is 10 ms in Linux/386.
 */
#define YIELD_s		0
#define YIELD_ns	1000000

void yield() {

    struct timespec st = {YIELD_s, YIELD_ns};

    if( (nanosleep(&st, NULL)) == -1 && (errno == EINVAL)) {
	perror("nanosleep");
	pthread_exit(NULL);
    }
}

/* Initialize bounded buffer */
int bbuf_init(bbuf_t *bbp) {

    if(bbp == NULL)
	return 0;

    bbp->in = 0;
    bbp->out = 0;
    bbp->cnt = 0;
    pthread_mutex_init(&(bbp->lock), NULL); /* I do not understand, but the 
					     * compiler complains when I use
					     * PTHREAD_MUTEX_INITIALIZER */
    return 1;
}

/* Print the bounded buffer members that matter */
void print_bbuf(bbuf_t *bbp) {
    printf("bbp->in = %d bbp->out = %d bbp_cnt = %d \n",
	   bbp->in, bbp->out, bbp->cnt);
}

/* To validate the value of the members in, out and cnt of bbuf_t */
int val(int n, int min, int max) {
    return( (min <= n) && (n <= max));
}

/* Ensure that the values of the members in, out and cnt are consistent */
int consist(int cnt, int in, int out) {
    return ( in == ((out + cnt) % BUF_SIZE) );
}

/* This is the code of the checker thread. It is used to ensure that
 * the bounded buffer has not been corrupted.
 * Every 100 ms it checks the values of: in, out and cnt.
 * This thread exits either if it detects the buffer has been corrupted
 * or if it does not detect any activity in 50 consecutive iterations, 
 * i.e. approximately 5s. */

/* These constants are used with nanosleep() and
 *  put a process to sleep for 100 ms */

#define SLEEP_s		0
#define SLEEP_ns	100000000

#define MAX_IDLE	50

void *check(void *arg) {
    bbuf_t *bbp = arg;
    int cnt[2], in[2], out[2];		/* values read */
    int idle;
    struct timespec st = {SLEEP_s, SLEEP_ns}; /* 100 ms */
    
    while(1) {
	pthread_mutex_lock( &(bbp->lock) );
	in[1] = bbp->in;
	out[1] = bbp->out;
	cnt[1] = bbp->cnt;
	pthread_mutex_unlock( &(bbp->lock) );
	if(in[1] == in[0] && out[1] == out[0] && cnt[1] == cnt[0] ) {
	    idle++;
	    if( idle >= MAX_IDLE ) {
		printf("Checking thread exiting:");
		print_bbuf(bbp);
		printf("\t no activity detected for some time.\n");
		pthread_exit(NULL);
	    }
	} else {
	    idle = 0;
	}
	if( !val(in[1], 0, BUF_SIZE - 1) ) {
	    printf("Invalid value in = %d \n", in[1]);
	    pthread_exit(NULL);
	} else if ( !val(out[1], 0, BUF_SIZE - 1) ) {
	    printf("Invalid value out = %d \n", out[1]);
	    pthread_exit(NULL);
	} else if ( !val(cnt[1], 0, BUF_SIZE) ) {
	    printf("Invalid value cnt = %d \n", cnt[1]);
	    pthread_exit(NULL);
	} else if ( !consist(cnt[1], in[1], out[1]) ) {
	    printf("Inconsistent buffer: cnt = %d in = %d out = %d \n",
		   cnt[1], in[1], out[1]);
	    pthread_exit(NULL);
	}
	if( (nanosleep(&st, NULL) == -1) && (errno == EINVAL)) {
	    perror("nanosleep");
	    pthread_exit(NULL);
	}
	in[0] = in[1];
	out[0] = out[1];
	cnt[0] = cnt[1];
    }
}    

/* The producer threads may use this code to
 *  enter one item into the buffer */

void bb_enter(bbuf_t *bbp, int me) {

    assert( bbp->cnt < BUF_SIZE);

    (bbp->buf)[bbp->in] = me;
    (bbp->in)++;
    (bbp->in) %= BUF_SIZE;
    (bbp->cnt)++;
}

/* This is the code for the producer threads.
 * You have to write it:
 *     the producers must write a message in the beginning, as well
 *     as in the end.
 *
 * To avoid busy waiting (or at least too much busy waiting) the producers
 * should yield, using the yield() defined above, if the buffer is
 * full. In that case, they should print a debugging message as well.
 *
 * Each producer should produce ITER (10 M) items: an integer with
 *  the id it receives in prod()'s argument.
 */
void *prod(void *arg) {
    parg_t *parg = (parg_t *)arg;
    bbuf_t *bbp = parg->bbp;
    int    me = parg->id;

    /* Add variables and code, if necessary */
}

/* The consumer threads may use this function to
 *  remove an item */

int bb_remove(bbuf_t *bbp) {
    int val;

    assert(bbp->cnt > 0);

    val = (bbp->buf)[bbp->out];
    (bbp->out)++;
    (bbp->out) %= BUF_SIZE;
    (bbp->cnt)--;
    return val;
}

/* This is the code for the consumer threads.
 * You have to write it:
 *     the consumers must write a message in the beginning, as well
 *     as in the end.
 *
 * To avoid busy waiting (or at least too much busy waiting) consumers
 * should yield, using the yield() defined above, if the buffer is
 * empty. In that case, they should print a debugging message as well.
 *
 * Each producer should consume ITER (10 M) items, and keep track of the 
 * producers of the items it consumes: use the cnt[] below.
 */
void *cons(void *arg) {
    bbuf_t *bbp = (bbuf_t *)arg;
    int cnt[PROD_THRD];

    /* Add variables and code, if necessary:
     *          do not forget to initialize cnt */

}

int main(int argc, char *argv[]) {

    int i;
    pthread_t *tid, ctid;
    parg_t *parg;
    bbuf_t *bbp;


    /* This is to measure the time it takes to run the program */
    struct tms t;
    clock_t start, end;
    long ticks = sysconf(_SC_CLK_TCK);

    start = times(&t);

    if( argc != 1 ) {
	printf(USAGE_STRING, argv[0]);
	exit(1);
    }

    /* Array for pthread_join() */
    if((tid = (pthread_t *) malloc((PROD_THRD + CONS_THRD) * sizeof(pthread_t)))
       == NULL ) {
	printf("Out of memory.\n");
	exit(2);
    }

    /* Allocate Bounded Buffer */
    if((bbp = (bbuf_t *) malloc(sizeof(bbuf_t))) == NULL ) {
	printf("Out of memory. \n");
	exit(2);
    }

    /* Initialize Bounded Buffer */
    if( bbuf_init(bbp) == 0 ) {
	printf("Failed to initialize bounded buffer\n");
	exit(3);
    }

    /* Arguments for producer threads */
    if((parg = (parg_t *) malloc( PROD_THRD * sizeof (parg_t))) == NULL ) {
	printf("Out of memory.\n");
	exit(2);
    } 

    /* Create checker thread */
    if( pthread_create(&ctid, NULL, check, bbp) )
	perror("pthread_create");
    printf("Created checker thread %u\n", (unsigned)ctid);
  

    /* Create consumer threads */
    for( i = 0; i < CONS_THRD; i++ ) {
	/* We pass the same data structure, the bounded buffer,
	 * to each consumer: they need to synchronize to access it */
	if( pthread_create(tid+i, NULL, cons, bbp) )
	    perror("pthread_create");
	printf("Created consumer thread %u\n", (unsigned)tid[i]);
    }

    /* Create producer threads */
    for( i = 0; i < PROD_THRD; i++ ) {
	/* Because we want each consumer to keep track of the
	 * producer of the items it consumes, we assign an
	 * id to each producer thread */
	parg[i].bbp = bbp;
	parg[i].id = i;
	if( pthread_create(tid+(i+CONS_THRD), NULL, prod, parg+i) )
	    perror("pthread_create");
	printf("Created producer thread %u (%d)\n", (unsigned)tid[i+CONS_THRD], i);
    }

    /* Join consumer and producer threads */
    for( i = 0; i < CONS_THRD + PROD_THRD; i ++ ) {
	if( pthread_join(tid[i], NULL) == 0 ) {
	    printf("Joined thread %u.\n", (unsigned)tid[i]);
	} else {
	    printf("Failed to join thread %u\n", (unsigned)tid[i]);
	}
    }

    /* Join checker thread */
    if( pthread_join(ctid, NULL) == 0 ) {
	printf("Joined checker thread %u.\n", (unsigned)ctid);
    } else {
	printf("Failed to join checker thread %u\n", (unsigned)ctid);
    }

    /* How long did it take to run this ? */
    end = times(&t);

    printf("Wall time %2.4f s \n", (float)(end - start) / ticks);

    return 0;

}
  
  
  
