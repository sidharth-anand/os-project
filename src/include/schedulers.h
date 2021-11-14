#ifndef SCHEDULERS_H
#define SHEDULERS_H

typedef void (*SchedulerFunction)(int processRunning[3], int processFinished[3], double timeQuantum);

void schedulerFCFS(int processRunning[3], int processFinished[3], double timeQuantum);
void schedulerRoundRobin(int processRunning[3], int processFinished[3], double timeQuantum);

#endif