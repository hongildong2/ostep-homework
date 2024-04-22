#ifndef THPOOL_H
#define THPOOL_H

typedef struct __job {
    void* (*job_func)(void*);
    void* job_args;
} job_t;

void run_jobs(job_t* jobs, int count);

#endif /* THPOOL_H */