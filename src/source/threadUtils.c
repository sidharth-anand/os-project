#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/threadUtils.h"

void startProcess(int pipe[2], ProcessArgs processArgs, int *running, int *finished, TaskFunction taskFunction, ProcessPipeFunction processPipeFunction)
{
    INIT_CONDITION(condition);
    INIT_MUTEX(mutex);

    ThreadArgs threadArgs = {.running = running,
                             .finished = finished,
                             .condition = &condition,
                             .mutex = &mutex};

    processArgs.threadArgs = &threadArgs;

    TaskArgs taskArgs = {.processArgs = &processArgs,
                         .taskFunction = taskFunction};

    pthread_t task_thread;
    pthread_create(&task_thread, NULL, startTask, (void*)&taskArgs);

    while (!(*finished))
    {
        M_LOCK(&mutex);

        if (*running)
            C_SIGNAL(&condition);

        M_UNLOCK(&mutex);
    }

    int threadRetVal;
    pthread_join(task_thread, (void*)&threadRetVal);

    C_DESTROY(&condition);
    M_DESTROY(&mutex);

    processPipeFunction(pipe, threadRetVal);

    _exit(EXIT_SUCCESS);
}

void* startTask(void *args)
{
    TaskArgs* taskArgs = (TaskArgs*)args;

    int result = taskArgs->taskFunction(taskArgs->processArgs);

    
    M_LOCK(taskArgs->processArgs->threadArgs->mutex);
    *(taskArgs->processArgs->threadArgs->finished) = 1;
    M_UNLOCK(taskArgs->processArgs->threadArgs->mutex);

    pthread_exit((void*)result);
}