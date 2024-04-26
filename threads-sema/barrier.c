#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"
#include "zem.h"

// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

// You likely need two semaphores to do this correctly, and some
// other integers to track things.
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;


typedef struct __barrier_t {
    // add semaphores and other information here
    int count;
    int num;
    zem_t sem_1;
    zem_t sem_2;
} barrier_t;


// the single barrier we are using for this program
barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {
    // initialization code goes here
    b->count = 0;
    b->num = num_threads;
    zem_init(&b->sem_1, 1);
    zem_init(&b->sem_2, 1);
}

void barrier(barrier_t *b, tinfo_t *t) {
    // barrier code goes here
    zem_wait(&b->sem_1);
    b->count++; // atomic since this code get binary semaphore, other threads cannot reach here.
    zem_post(&b->sem_1);
    printf("thread num : %d, begin to wait#\n", t->thread_id);
    while (b->count < b->num) {
        /*
            The Very first thread entering here call zem_wait twice, making semaphore value to 0 and wait.
            Even if other threads came in, they all trapped here.
            But The Very Last Thread came here ignore this while loop, thus does not wait, call zem_post
            Then triggering cond, waking up all the other threads, as while loop is fulfilled, they all exit.
        */
        zem_wait(&b->sem_2); 
        printf("thread num : %d, spin? or exiting?\n", t->thread_id);
    }
    zem_post(&b->sem_2); 
    // do not reach until all threads are instantiated
}

//
// XXX: don't change below here (just run it!)
//

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("child %d: before\n", t->thread_id);

    barrier(&b, t);

    printf("child %d: after\n", t->thread_id);
    return NULL;
}


// run with a single argument indicating the number of 
// threads you wish to create (1 or more)
int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);
    
    int i;
    for (i = 0; i < num_threads; i++) {
	t[i].thread_id = i;
	Pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++) 
	Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}

