#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>

#include "hoh_ll.h"

static int i = 0;
// for init
static pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER; 
void __init_node(locked_node_t* node);
int __traverse(hh_list_t* node);

void hh_list_init(hh_list_t* h)
{
    pthread_mutex_lock(&global_lock);
    if (h->head != NULL) {
        // already init
        return;
    }

    // dummy node in head
    locked_node_t* new_node = malloc(sizeof(locked_node_t));
    new_node->key = -1;
    new_node->next = NULL;
    h->head = new_node;

    pthread_mutex_unlock(&global_lock);
}

void hh_list_insert(hh_list_t* h)
{
    locked_node_t* new_node = malloc(sizeof(locked_node_t));
    __init_node(new_node);

    // new's next is dummy(head)'s next
    pthread_mutex_lock(&h->head->lock);
    new_node->next = h->head->next;


    // dummy is always at head;
    // dummy's next is new node
    h->head->next = new_node;
    pthread_mutex_unlock(&h->head->lock);
}

void __init_node(locked_node_t* node)
{
    node->key = i++;
    pthread_mutex_init(&node->lock, NULL);
}

int __traverse(hh_list_t* h)
{
    locked_node_t* head = h->head;
    if (head != NULL && head->next == NULL) {
        return -1;
    }
    head = head->next; //real head
    
    int val = 0;
    while (head != NULL) {
        pthread_mutex_lock(&head->lock);
        val = head->key;
        pthread_mutex_unlock(&head->lock);
        head = head->next;
    }

    return val;
}