#ifndef SCHEDULERS_H
#define SHEDULERS_H

typedef void (*SchedulerFunction)(int processRunning[3], int processFinished[3], double timeQuantum, char *perfFilename);
/*
    Include file for the profile.c file
*/
void schedulerFCFS(int processRunning[3], int processFinished[3], double timeQuantum, char *perfFilename);
void schedulerRoundRobin(int processRunning[3], int processFinished[3], double timeQuantum, char *perfFilename);

#endif