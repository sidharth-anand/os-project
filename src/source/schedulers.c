#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "../include/schedulers.h"
#include "../include/performance.h"
#include "../include/utils.h"

//FCFS algorithm
void schedulerFCFS(int processRunning[3], int processFinished[3], double timeQuantum, char* perfFilename)
{
    struct timespec globalStart, globalEnd;

    PerformanceParameters perfParams[3];

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalStart);

    for (int i = 0; i < 3; i++)
    {
        perfParams[i].globalStart = globalStart;
        perfParams[i].totalBoostTime = 0;
    }

    for (int i = 0; i < 3; i++)
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &perfParams[i].localStart);

        processRunning[i] = 1;

        while (!processFinished[i])
            continue;

        processRunning[i] = 0;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &perfParams[i].localEnd);

        perfParams[i].totalBoostTime = getElapsedTime(perfParams[i].localStart, perfParams[i].localEnd);
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalEnd);

    for (int i = 0; i < 3; i++)
        perfParams[i].globalEnd = globalEnd;

    reportPerformance(perfParams, perfFilename);
}

//Round Robin
void schedulerRoundRobin(int processRunning[3], int processFinished[3], double timeQuantum, char* perfFilename)
{
    int allFinished = 0;

    int processStarted[3] = {0, 0, 0};
    int processMarked[3] = {0, 0, 0};

    PerformanceParameters perfParams[3];

    struct timespec globalStart, globalEnd;

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalStart);

    for (int i = 0; i < 3; i++)
    {
        perfParams[i].globalStart = globalStart;
        perfParams[i].totalBoostTime = 0.f;
    }

    while (!allFinished)
    {
        allFinished = 1;

        for (int i = 0; i < 3; i++)
        {
            if (!processStarted[i])
            {
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &perfParams[i].localStart);
                processStarted[i] = 1;
            }

            if (!processFinished[i])
            {
                allFinished = 0;

                struct timespec quantumStart, quantumEnd;

                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &quantumStart);
                double elapsedTime = 0;

                processRunning[i] = 1;

                while (!processFinished[i] && elapsedTime <= timeQuantum)
                {
                    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &quantumEnd);
                    elapsedTime = getElapsedTime(quantumStart, quantumEnd);
                    continue;
                }

                processRunning[i] = 0;

                perfParams[i].totalBoostTime += elapsedTime;
            }

            if (processFinished[i] && !processMarked[i])
            {
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &perfParams[i].localEnd);
                processMarked[i] = 1;
            }
        }
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalEnd);

    for (int i = 0; i < 3; i++)
        perfParams[i].globalEnd = globalEnd;

    reportPerformance(perfParams, perfFilename);
}