#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "thpool.h"


int __wait(pthread_t* threads, int* wait_list, int count);

void run_jobs(job_t* jobs, int count)
{
    pthread_t* a_thpool = malloc(sizeof(pthread_t) * count);
    int* a_wait_list = malloc(sizeof(int) * count);
    memset(a_wait_list, 0, sizeof(int) * count);
    int error = 0;

    for (int i = 0; i < count; ++i) {
        job_t job = jobs[i];

        if((error = pthread_create(&a_thpool[i], NULL, job.job_func, job.job_args)) != 0) {
            goto release;
        }

    }


    // error will be raised when __wait returns non-zero abnormal rc
    error = __wait(a_thpool, a_wait_list, count);


release:
    free(a_thpool);
    free(a_wait_list);
    if (error) exit(1);
}

int __wait(pthread_t* threads, int* wait_list, int count)
{
    for (int i = 0; i < count; ++i) {
        if (wait_list[i] == 1) continue; // already done
        
        int rs = pthread_join(threads[i], NULL);
        if (rs != 0) return -1;
        
        wait_list[i] = 1;
    }

    int k;
    for (k = 0 ;  k < count; ++k) {
        if (wait_list[k] == 0) break; // not done
    }

    if (k >= count) return 0; // all loop done without break end cond


    return __wait(threads, wait_list, count);
}