#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

#include "zem.h"


void zem_init(zem_t* s, int value)
{
    printf("Semaphore intiation with value :%d\n", value);
    s->value = value;
    pthread_cond_init(&(s->cond), NULL);
    pthread_mutex_init(&(s->lock), NULL);
    printf("Semaphore initiated with value :%d\n", s->value);
}

void zem_wait(zem_t* s)
{
    pthread_mutex_lock(&(s->lock));
    while(s->value <= 0) {
        pthread_cond_wait(&(s->cond), &(s->lock));
    }
    s->value--;
    pthread_mutex_unlock(&(s->lock));
}
void zem_post(zem_t* s)
{
    pthread_mutex_lock(&(s->lock));
    s->value++;
    pthread_cond_signal(&(s->cond));
    pthread_mutex_unlock(&(s->lock));
}
