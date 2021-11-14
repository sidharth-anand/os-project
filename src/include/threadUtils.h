#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

#include <pthread.h>

#include "pipeUtils.h"

#define INIT_MUTEX(mutex) pthread_mutex_t mutex;\
                          pthread_mutex_init(&mutex, NULL)

#define M_LOCK(mutex) pthread_mutex_lock(mutex)
#define M_UNLOCK(mutex) pthread_mutex_unlock(mutex)
#define M_DESTROY(mutex) pthread_mutex_destroy(mutex)

#define INIT_CONDITION(condition) pthread_cond_t condition;\
                                    pthread_cond_init(&condition, NULL)

#define C_WAIT(condition, mutex) pthread_cond_wait(condition, mutex)
#define C_SIGNAL(condition) pthread_cond_signal(condition)
#define C_DESTROY(condition) pthread_cond_destroy(condition)

#define PROC_ARGS_WAIT(processArgs) while(!*(processArgs->threadArgs->running)) \
                                        C_WAIT(processArgs->threadArgs->condition, processArgs->threadArgs->mutex)

#define LOCK_WAIT_UNLOCK(processArgs) M_LOCK(processArgs->threadArgs->mutex); \
                                        PROC_ARGS_WAIT(processArgs);\
                                        M_UNLOCK(processArgs->threadArgs->mutex)

typedef struct _ThreadArgs
{
    int*                running;
    int*                finished;

    pthread_cond_t*     condition;
    pthread_mutex_t*    mutex;

} ThreadArgs;

typedef struct _ProcessArgs
{
    int*          numbers;
    int           length;

    char*         filename;

    ThreadArgs*   threadArgs;

} ProcessArgs;

typedef void (*ProcessPipeFunction)(int pipe[2], int processResult, double elapsedTime);
typedef int (*TaskFunction)(ProcessArgs* processArgs);

typedef struct _TaskArgs
{
    ProcessArgs*   processArgs;
    TaskFunction   taskFunction;

} TaskArgs;

void startProcess(int pipe[2], ProcessArgs processArgs, int* running, int* finished, TaskFunction taskFunction, ProcessPipeFunction processPipeFunction);
void* startTask(void* taskArgs);

#endif