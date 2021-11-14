#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/profile.h"
#include "../include/processes.h"

int process1Task(ProcessArgs *processArgs)
{
    LOCK_WAIT_UNLOCK(processArgs);

    int sum = 0;

    for (int i = 0; i < processArgs->length; i++)
    {
        M_LOCK(processArgs->threadArgs->mutex);

        PROC_ARGS_WAIT(processArgs);

        sum += processArgs->numbers[i];

        M_UNLOCK(processArgs->threadArgs->mutex);
    }

    return sum;
}

void process1PipeFunction(int pipe[2], int processResult, double elapsedTime)
{
    CLOSE_READ(pipe);

    char message[100];
    char time[100];
    sprintf(message, "%d\n", processResult);
    sprintf(time, "%f\n", elapsedTime);

    write(pipe[PIPE_WRITE], message, strlen(message));
    write(pipe[PIPE_WRITE], time, strlen(time));

    CLOSE_WRITE(pipe);
}

int process2Task(ProcessArgs *processArgs)
{
    LOCK_WAIT_UNLOCK(processArgs);

    FILE *fp;
    char *line = NULL;

    size_t len = 0;
    ssize_t read;

    fp = fopen(processArgs->filename, "r");
    if (fp == NULL)
        _exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        M_LOCK(processArgs->threadArgs->mutex);

        PROC_ARGS_WAIT(processArgs);

        write(STDOUT_FILENO, line, strlen(line));

        M_UNLOCK(processArgs->threadArgs->mutex);
    }

    fclose(fp);
    if (line)
        free(line);

    return 0;
}

void process2PipeFunction(int pipe[2], int processResult, double elapsedTime)
{
    CLOSE_READ(pipe);

    char message[] = "\nDone Printing\n";
    char time[100];
    sprintf(time, "\n%f\n", elapsedTime);

    write(pipe[PIPE_WRITE], message, strlen(message));
    write(STDOUT_FILENO, time, strlen(time));

    CLOSE_WRITE(pipe);
}

int process3Task(ProcessArgs *processArgs)
{
    LOCK_WAIT_UNLOCK(processArgs);

    FILE *fp;
    char *line = NULL;

    size_t len = 0;
    ssize_t read;

    fp = fopen(processArgs->filename, "r");
    if (fp == NULL)
        _exit(EXIT_FAILURE);

    int sum = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        M_LOCK(processArgs->threadArgs->mutex);

        PROC_ARGS_WAIT(processArgs);

        char *end;
        long num = strtol(line, &end, 10);
        sum += num;

        M_UNLOCK(processArgs->threadArgs->mutex);
    }

    fclose(fp);
    if (line)
        free(line);

    return sum;
}

void process3PipeFunction(int pipe[2], int processResult, double elapsedTime)
{
    CLOSE_READ(pipe);

    char message[100];
    char time[100];
    sprintf(message, "%d\n", processResult);
    sprintf(time, "%lf\n", elapsedTime);

    write(pipe[PIPE_WRITE], message, strlen(message));
    write(pipe[PIPE_WRITE], time, strlen(time));

    CLOSE_WRITE(pipe);
}