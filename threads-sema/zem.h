#ifndef ZEM_H
#define ZEM_H
#include <pthread.h>

typedef struct __zem_t {
    int value;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} zem_t;
 

void zem_init(zem_t* s, int value);
void zem_wait(zem_t* s);
void zem_post(zem_t* s);

#endif /* ZEM_H */