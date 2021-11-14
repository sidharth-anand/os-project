#ifndef PROFILE_H
#define PROFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

#define CONCATENATE_DIRECT(X, Y) X##Y
#define CONCATENATE(X, Y) CONCATENATE_DIRECT(X, Y)
#define LINEVARNAME(X) CONCATENATE(X, __LINE__)

#define PROFILE_LINE(LINE, LABEL)                                                            \
    struct timespec LINEVARNAME(start);                                                      \
    struct timespec LINEVARNAME(stop);                                                       \
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &LINEVARNAME(start));                             \
    LINE;                                                                                    \
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &LINEVARNAME(stop));                              \
    char time[100];                                                                          \
    sprintf(time, "%s: %f\n", LABEL, getElapsedTime(LINEVARNAME(start), LINEVARNAME(stop))); \
    write(STDOUT_FILENO, time, strlen(time));

#endif