#ifndef CONCURRENT_COUNTER
#define CONCURRENT_COUNTER

#include "pthread.h"
#include <sys/_pthread/_pthread_mutex_t.h>

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void counter_init(counter_t* counter);
void counter_increment(counter_t* counter);
void counter_decrement(counter_t* counter);
int counter_get(counter_t* counter);

#endif /* CONCURRENT_COUNTER_H */