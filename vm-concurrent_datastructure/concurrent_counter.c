#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

#include "concurrent_counter.h"


void counter_init(counter_t* counter)
{
    counter->value = 0;
    pthread_mutex_init(&counter->lock, NULL);
}

void counter_increment(counter_t* counter)
{
    pthread_mutex_lock(&counter->lock);
    
    counter->value += 1;

    pthread_mutex_unlock(&counter->lock);
}

void counter_decrement(counter_t* counter)
{
    pthread_mutex_lock(&counter->lock);
    counter->value -= 1;
    pthread_mutex_unlock(&counter->lock);
}

int counter_get(counter_t* counter)
{
    pthread_mutex_lock(&counter->lock);
    int rc = counter->value;
    pthread_mutex_unlock(&counter->lock);
    return rc;
}