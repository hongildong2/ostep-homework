#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common_threads.h"
#include "zem.h"
//
// Your code goes in the structure and functions below
// reader need to acquire write lock.
// If there is no current write lock (write_lock is at 0), readers just can proceed to reading.
// readers share write lock, read lock

typedef struct __rwlock_t {
    int writer; // mark that writer is waiting
    int readers; // reader status check for getting write lock
    zem_t write_lock;
    pthread_mutex_t lock;
    pthread_cond_t writer_signal; // exclusive mutex wakeup
} rwlock_t;


void rwlock_init(rwlock_t *rw) {
    zem_init(&rw->write_lock, 1);
    Pthread_mutex_init(&rw->lock, NULL);
    Pthread_cond_init(&rw->writer_signal, NULL);
    rw->readers = 0;
    rw->writer = 0;
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    Pthread_mutex_lock(&rw->lock);
    if (rw->writer == 1) {
        Pthread_cond_signal(&rw->writer_signal); // send signal to writer exclusively
        Pthread_mutex_unlock(&rw->lock);
        return; 
    }
    rw->readers++;
    // printf("%d reader count\n", rw->readers);
    if (rw->readers == 1) {
        zem_wait(&rw->write_lock); // first reader get write lock.
    }
    Pthread_mutex_unlock(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    Pthread_mutex_lock(&rw->lock);
    rw->readers--; // this is a critical section too
    if (rw->readers == 0) {
        zem_post(&rw->write_lock);
        if (rw->writer == 1) {
            
            Pthread_cond_signal(&rw->writer_signal); // send signal to writer exclusively
            Pthread_mutex_unlock(&rw->lock);
        }
    }
    Pthread_mutex_unlock(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    // 여기서 그냥 lock 먹으면 write lock 이 먹는거아닌가?
    Pthread_mutex_lock(&rw->lock);
    while (rw->readers != 0) {
        rw->writer = 1;
        Pthread_cond_wait(&rw->writer_signal, &rw->lock);
    }
    zem_wait(&rw->write_lock);
}

void rwlock_release_writelock(rwlock_t *rw) {
    rw->writer = 0;
    zem_post(&rw->write_lock);
    pthread_mutex_unlock(&rw->lock);
}

//
// Don't change the code below (just use it!)
// 

int loops;
int value = 0;

rwlock_t lock;

void *reader(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
	rwlock_acquire_readlock(&lock);
	printf("read %d\n", value);
    sleep(1);

	rwlock_release_readlock(&lock);
    }
    return NULL;
}

void *writer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
	rwlock_acquire_writelock(&lock);
	value++;
	printf("write %d\n", value);
	rwlock_release_writelock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int num_readers = atoi(argv[1]);
    int num_writers = atoi(argv[2]);
    loops = atoi(argv[3]);

    pthread_t pr[num_readers], pw[num_writers];

    rwlock_init(&lock);

    printf("begin\n");

    int i;
    for (i = 0; i < num_readers; i++)
	Pthread_create(&pr[i], NULL, reader, NULL);
    for (i = 0; i < num_writers; i++)
	Pthread_create(&pw[i], NULL, writer, NULL);

    for (i = 0; i < num_readers; i++)
	Pthread_join(pr[i], NULL);
    for (i = 0; i < num_writers; i++)
	Pthread_join(pw[i], NULL);

    printf("end: value %d\n", value);

    return 0;
}

