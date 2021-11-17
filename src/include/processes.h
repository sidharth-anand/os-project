#ifndef PROCESSES_H
#define PROCESSES_H

#include "threadUtils.h"

/*
    Include file for the processes.c file
*/
int process1Task(ProcessArgs* processArgs);
void process1PipeFunction(int pipe[2], int processResult, double elapsedTime);

int process2Task(ProcessArgs* processArgs);
void process2PipeFunction(int pipe[2], int processResult, double elapsedTime);

int process3Task(ProcessArgs* processArgs);
void process3PipeFunction(int pipe[2], int processResult, double elapsedTime);

#endif