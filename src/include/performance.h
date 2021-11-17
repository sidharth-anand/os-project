#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <time.h>
/*
    Include file for the performance.c file
*/
typedef struct _PerformanceParameters 
{
    struct timespec globalStart;
    struct timespec globalEnd;

    struct timespec localStart;
    struct timespec localEnd;

    double totalBoostTime;

} PerformanceParameters;

typedef struct _ProcessPerformance
{
    double processStart;
    double turnAroundTime;
    double waitingTime;

} ProcessPerformance;

ProcessPerformance getProcessPerformance(PerformanceParameters parameters);

void reportPerformance(PerformanceParameters performanceParameters[3], char* perfFilename);

#endif