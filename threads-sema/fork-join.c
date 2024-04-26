#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "zem.h"

zem_t g_s; 

void *child(void *arg) {
    printf("child\n");
    // use zemaphore here

    sleep(1);
    zem_post(&g_s);

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    // init zemaphore here
    zem_init(&g_s, 0);


    pthread_create(&p, NULL, child, NULL);
    // use zemaphore here
    zem_wait(&g_s);


    printf("parent: end\n");
    return 0;
}

