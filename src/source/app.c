#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include "../include/app.h"
#include "../include/pipeTransport.h"
#include "../include/processes.h"
#include "../include/schedulers.h"
#include "../include/utils.h"

AppArgs appInit(int length, double timeQuantum, int scheduler, char *process2Filename, char *process3Filename)
{
    AppArgs appArgs;

    appArgs.length = length;

    appArgs.numbers = malloc(sizeof(int) * appArgs.length);
    for (int i = 0; i < appArgs.length; i++)
        appArgs.numbers[i] = i;

    // char process2Filename[] = "data/file2.txt";
    // char process3Filename[] = "data/file3.txt";

    appArgs.process2Filename = malloc(sizeof(char) * (strlen(process2Filename)));
    memcpy(appArgs.process2Filename, process2Filename, strlen(process2Filename));

    appArgs.process3Filename = malloc(sizeof(char) * (strlen(process3Filename)));
    memcpy(appArgs.process3Filename, process3Filename, strlen(process3Filename));

    if (scheduler == 1)
        appArgs.schedulerChoice = schedulerRoundRobin;
    else
        appArgs.schedulerChoice = schedulerFCFS;

    appArgs.timeQuantum = timeQuantum;

    return appArgs;
}

void appRun(AppArgs appArgs)
{
    int pipefds[3][2];
    pid_t pids[3];

    int *processRunning = intializeSharedMemory();
    int *processFinished = intializeSharedMemory();

    ProcessArgs processArgs[3] = {
        {.length = appArgs.length, .numbers = appArgs.numbers},
        {.filename = appArgs.process2Filename},
        {.filename = appArgs.process3Filename}};

    TaskFunction taskFunctions[3] = {
        process1Task,
        process2Task,
        process3Task};

    ProcessPipeFunction pipeFunctions[3] = {
        process1PipeFunction,
        process2PipeFunction,
        process3PipeFunction};

    for (int i = 0; i < 3; i++)
    {
        if (pipe(pipefds[i]) == -1)
            exit(EXIT_FAILURE);

        pids[i] = fork();

        if (pids[i] < 0)
            exit(EXIT_FAILURE);
        else if (pids[i] == 0)
            startProcess(pipefds[i], processArgs[i], &processRunning[i], &processFinished[i], taskFunctions[i], pipeFunctions[i]);
    }

    pthread_t listener_thread;
    pthread_create(&listener_thread, NULL, start_listening, (void *)pipefds);

    appArgs.schedulerChoice(processRunning, processFinished, appArgs.timeQuantum);

    pthread_join(listener_thread, NULL);

    for (int i = 0; i < 3; i++)
        wait((int *)&pids[i]);

    munmap(processRunning, sizeof(int) * 3);
    munmap(processFinished, sizeof(int) * 3);
}

void appDestroy(AppArgs appArgs)
{
    free(appArgs.numbers);
    free(appArgs.process2Filename);
    free(appArgs.process3Filename);
}