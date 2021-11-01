#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "../include/schedulers.h"
#include "../include/performance.h"
#include "../include/utils.h"

void schedulerFCFS(int processRunning[3], int processFinished[3], float timeQuantum)
{
    struct timespec globalStart, globalEnd;

    PerformanceParameters perfParams[3];

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalStart);

    for(int i = 0; i < 3; i++)
    {
        perfParams[i].globalStart = globalStart;
        perfParams[i].totalBoostTime = 0;
    }
    
    for(int i = 0; i < 3; i++)
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &perfParams[i].localStart);

        processRunning[i] = 1;

        while(!processFinished[i])
            sleep(timeQuantum);

        processRunning[i] = 0;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &perfParams[i].localEnd);

        perfParams[i].totalBoostTime = getElapsedTime(perfParams[i].localStart, perfParams[i].localEnd);
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalEnd);

    for(int i = 0; i < 3; i++)
        perfParams[i].globalEnd = globalEnd;

    reportPerformance(perfParams);
}

void schedulerRoundRobin(int processRunning[3], int processFinished[3], float timeQuantum)
{
    int allFinished = 0;

    int processStarted[3] = {0, 0, 0};
    PerformanceParameters perfParams[3];

    struct timespec globalStart, globalEnd;

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalStart);

    for(int i = 0; i < 3; i++)
    {
        perfParams[i].globalStart = globalStart;
        perfParams[i].totalBoostTime = 0;
    }
    
    while(!allFinished)
    {
        allFinished = 1;

        for(int i = 0; i < 3; i++)
        {
            if(!processStarted[i] && !processFinished[i])
            {
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &perfParams[i].localStart);
                processStarted[i] = 1;
            }

            if(!processFinished[i])
            {
                processRunning[i] = 1;

                sleep(timeQuantum);

                processRunning[i] = 0;

                allFinished = 0;

                perfParams[i].totalBoostTime += timeQuantum;
            }
            else if(processStarted[i])
            {
                clock_gettime(CLOCK_THREAD_CPUTIME_ID, &perfParams[i].localEnd);
                processStarted[i] = 0;
            }
        }
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &globalEnd);

    for(int i = 0; i < 3; i++)
        perfParams[i].globalEnd = globalEnd;

    reportPerformance(perfParams);
}