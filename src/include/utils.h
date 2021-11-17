#ifndef UTILS_H
#define UTILS_H

#include <time.h>
/*
    Include file for the utils.c file
*/
int *intializeSharedMemory();

double getElapsedTime(struct timespec start, struct timespec end);

#endif