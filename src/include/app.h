#ifndef APP_H
#define APP_H

#include "schedulers.h"

typedef struct _AppArgs
{
    int length;
    int *numbers;
    double timeQuantum;

    char *process2Filename;
    char *process3Filename;

    SchedulerFunction schedulerChoice;

} AppArgs;

AppArgs appInit(int length, double timeQuantum, int scheduler, char *process2Filename, char *process3Filename);
void appRun(AppArgs appArgs);
void appDestroy(AppArgs appArgs);

#endif