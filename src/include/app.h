#ifndef APP_H
#define APP_H

#include "schedulers.h"
/*
    Include file for the app.c file
*/
typedef struct _AppArgs
{
    int length;
    int *numbers;
    double timeQuantum;

    char *process2Filename;
    char *process3Filename;
    char *perfFilename;

    SchedulerFunction schedulerChoice;

} AppArgs;

AppArgs appInit(int length, double timeQuantum, int scheduler, char *process2Filename, char *process3Filename, char *perfFilename);
void appRun(AppArgs appArgs);
void appDestroy(AppArgs appArgs);

#endif