#ifndef UTILS_H
#define UTILS_H

#include <time.h>

int *intializeSharedMemory();

double getElapsedTime(struct timespec start, struct timespec end);

#endif