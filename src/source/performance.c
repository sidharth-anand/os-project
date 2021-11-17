#include <stdio.h>
#include <unistd.h>

#include "../include/performance.h"
#include "../include/utils.h"

//Get the performance stats from the process - Start time, Waiting Time and Turnaround Time
ProcessPerformance getProcessPerformance(PerformanceParameters parameters)
{
    double totalElapsedTime = getElapsedTime(parameters.globalStart, parameters.globalEnd);

    ProcessPerformance processPerformance;

    processPerformance.processStart = getElapsedTime(parameters.globalStart, parameters.localStart);
    processPerformance.turnAroundTime = getElapsedTime(parameters.globalStart, parameters.localEnd);
    processPerformance.waitingTime = processPerformance.turnAroundTime - parameters.totalBoostTime;

    return processPerformance;
} 

//Fetch and write the performance stats into perf.txt file
void reportPerformance(PerformanceParameters performanceParameters[3], char* perfFilename)
{
    sleep(1);

    ProcessPerformance processPerfs[3];

    for(int i = 0; i < 3; i++)
        processPerfs[i] = getProcessPerformance(performanceParameters[i]);

    for(int i = 0; i < 3; i++)
        printf("Process %d: start - %f\t waiting - %f\t turnaround - %f\n", i + 1, processPerfs[i].processStart, processPerfs[i].waitingTime, processPerfs[i].turnAroundTime);

    FILE* perfFile;
    perfFile = fopen(perfFilename, "wb+");

    for(int i = 0; i < 3; i++)
        fprintf(perfFile, "%d-%f-%f-%f\n", i + 1, processPerfs[i].processStart, processPerfs[i].waitingTime, processPerfs[i].turnAroundTime);

    fclose(perfFile);
}