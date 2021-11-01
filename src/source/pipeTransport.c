#include <unistd.h>
#include <pthread.h>

#include "../include/pipeTransport.h"
#include "../include/pipeUtils.h"

void* listen_and_print(void* pipeArg)
{
    int* pipe = (int*)(pipeArg);

    char buf;
    char newline = '\n';

    CLOSE_WRITE(pipe);

    while (read(pipe[PIPE_READ], &buf, 1) > 0)
        write(STDOUT_FILENO, (void*)&buf, 1);

    CLOSE_READ(pipe);

    pthread_exit(0);
}

void* start_listening(void* pipefdsArg)
{
    int* pipefds_ptr = (int*)pipefdsArg;

    int pipefds[3][2];

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 2; j++)
            pipefds[i][j] = *(pipefds_ptr + 2 * i + j);
    }

    pthread_t tids[3];

    for(int i = 0; i < 3; i++)
        pthread_create(&tids[i], NULL, listen_and_print, (void*)(pipefds[i]));

    for(int i = 0; i < 3; i++)
        pthread_join(tids[i], NULL);

    pthread_exit(0);
}