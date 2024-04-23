#ifndef SCALABLE_COUNTER_H
#define SCALABLE_COUNTER_H

#include "concurrent_counter.h"
#include <sys/_pthread/_pthread_mutex_t.h>
#define CPU_NUM (4)

typedef struct __scalable_counter_t {
    int global_count;
    pthread_mutex_t global_lock;
    int local_count[CPU_NUM];
    pthread_mutex_t local_locks[CPU_NUM];
    int threshold; // local -> global update counter
} scalable_counter_t;

void init_lock(scalable_counter_t* c);
void update(scalable_counter_t* c);
int get(scalable_counter_t* c);


#endif