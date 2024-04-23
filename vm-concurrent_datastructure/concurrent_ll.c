#include "concurrent_ll.h"

#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>

static int count = 0;

// init
void linked_list_init(linked_list_t* l)
{
    // new node
    l->head = NULL;
    pthread_mutex_init(&l->lock, NULL);
}

//insert
void linked_list_insert(linked_list_t* l)
{
    pthread_mutex_lock(&l->lock);

    node_t* new_node = malloc(sizeof(node_t));
    new_node->key = count++;
    new_node->next = NULL;
    
    if (l->head == NULL) {
        l->head = new_node;
        pthread_mutex_unlock(&l->lock);
    }

    new_node->next = l->head;
    l->head = new_node;

    pthread_mutex_unlock(&l->lock);
}

//lookup
int linked_list_lookup(linked_list_t* l)
{
    pthread_mutex_lock(&l->lock);

    if (l->head == NULL) {
        pthread_mutex_unlock(&l->lock);
        return 0;
    }
    int random = 5;

    node_t* current = l->head;
    while (current != NULL) {
        if (current->key == random) {
            pthread_mutex_unlock(&l->lock);
            return random;
        }

        current = current->next;
    }
    pthread_mutex_unlock(&l->lock);
    return 0;
}