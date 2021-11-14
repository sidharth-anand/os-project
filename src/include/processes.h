#ifndef PROCESSES_H
#define PROCESSES_H

#include "threadUtils.h"

int process1Task(ProcessArgs* processArgs);
void process1PipeFunction(int pipe[2], int processResult, double elapsedTime);

int process2Task(ProcessArgs* processArgs);
void process2PipeFunction(int pipe[2], int processResult, double elapsedTime);

int process3Task(ProcessArgs* processArgs);
void process3PipeFunction(int pipe[2], int processResult, double elapsedTime);

#endif