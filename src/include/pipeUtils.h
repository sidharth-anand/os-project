/*
    Include file for the pipeUtils.c file
*/
#ifndef PIPE_UTILS_H
#define PIPE_UTILS_H

#define PIPE_READ 0
#define PIPE_WRITE 1

#define CLOSE_READ(x) close(x[PIPE_READ])
#define CLOSE_WRITE(x) close(x[PIPE_WRITE])

#endif