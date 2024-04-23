#include <pthread.h>
#include <sys/types.h>

#include "scalable_counter.h"
#define THRESHOLD (50)

static int inc = 0;

void init_lock(scalable_counter_t* c)
{
    c->global_count = 0;
    pthread_mutex_init(&c->global_lock, NULL);
    for (int i = 0; i < CPU_NUM; ++i) {
        c->local_count[i] = 0;
        pthread_mutex_init(&c->local_locks[i], NULL);
    }
    c->threshold = THRESHOLD;
}
void update(scalable_counter_t* c)
{

    // 인자넣기 귀찮아서 그냥 고정
    int cpu_n = inc++ % CPU_NUM;
    int amount = 25;

    //get local lock, update local counter
    pthread_mutex_lock(&c->local_locks[cpu_n]);

    c->local_count[cpu_n] += amount;

    if (c->local_count[cpu_n] > c->threshold) {
        // if count > threshold, get global lock and local->global
        pthread_mutex_lock(&c->global_lock);
        c->global_count += c->local_count[cpu_n];
        pthread_mutex_unlock(&c->global_lock);

        c->local_count[cpu_n] = 0;
        // local<-0, release global lock
    }
    

    // release local lock
    pthread_mutex_unlock(&c->local_locks[cpu_n]);
}
int get(scalable_counter_t* c)
{
    // get global lock
    pthread_mutex_lock(&c->global_lock);
    int co = c->global_count;
    pthread_mutex_unlock(&c->global_lock);
    // copy val
    // release
    return co;
}