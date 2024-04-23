#ifndef HOH_LL_H
#define HOH_LL_H

#include <sys/_pthread/_pthread_mutex_t.h>

typedef struct __locked_node_t {
    int key;
    struct __locked_node_t* next;
    pthread_mutex_t lock;
} locked_node_t;

typedef struct __hh_list_t {
    locked_node_t* head;
} hh_list_t;

void hh_list_init(hh_list_t* h);
void hh_list_insert(hh_list_t* h);

#endif /* HOH_LL_H */