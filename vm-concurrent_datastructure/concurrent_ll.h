#ifndef CONCURRENT_LL_H
#define CONCURRENT_LL_H

#include <sys/_pthread/_pthread_mutex_t.h>
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

typedef struct __linked_list_t {
    node_t* head;
    pthread_mutex_t lock;
} linked_list_t;

// init
void linked_list_init(linked_list_t* l);

//insert
void linked_list_insert(linked_list_t* l); // 귀찮아서 key는 자동생성

//lookup
int linked_list_lookup(linked_list_t* l); // 자동생성으로 룩업하기 ㅋㅋ

#endif /* CONCURRENT_LL_H */