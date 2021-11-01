#ifndef SCHEDULERS_H
#define SHEDULERS_H

typedef void (*SchedulerFunction)(int processRunning[3], int processFinished[3], float time_quantum);

void schedulerFCFS(int processRunning[3], int processFinished[3], float time_quantum);
void schedulerRoundRobin(int processRunning[3], int processFinished[3], float time_quantum);

#endif