#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <time.h>

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

void reportPerformance(PerformanceParameters performanceParameters[3]);

#endif