#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_timeval.h>
#include <sys/time.h>
#include <string.h>

#include "concurrent_counter.h"
#include "thpool.h"

static struct timeval s_start_time;
static struct timeval s_end_time;

void start_time(void);
void end_time(void);
void print_time(char*);
void test_datastructure(void* (*func)(void*));

int main(int argc, char** argv)
{
    if (argc != 2) return 1;    
    
    int count;
    sscanf(argv[1], "%d", &count); // danger!

    
    
    job_t* a_jobs = malloc(sizeof(job_t) * count);
    counter_t counter;
    counter_init(&counter);


    for (int i = 0; i < count; ++i) {
        a_jobs[i].job_args = &counter;
        a_jobs[i].job_func = (void*) counter_increment;
    }

    counter_init(&counter);
    start_time();
    for (int s = 0; s < count; ++s) {
        counter_increment(&counter);
    }
    end_time();
    print_time("TESTING SINGLE THREAD COUNTER!");


    
    start_time();
    run_jobs(a_jobs, count);
    end_time();
    print_time("TESTING THREADED COUNTER!");



    return 0;
}

void test_datastructure(void* (*func)(void*))
{
    // open threads

    // send thread "func" to test
}
void start_time(void)
{
    gettimeofday(&s_start_time, NULL);
}

void end_time(void)
{
    gettimeofday(&s_end_time, NULL);
}

void print_time(char* message)
{
    printf("%s, passed : %d\n", message, s_end_time.tv_usec - s_start_time.tv_usec);
}