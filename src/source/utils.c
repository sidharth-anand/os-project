#include <stddef.h>
#include <string.h>

#include <sys/mman.h>

#include "../include/utils.h"

//Initialize shared memory
int* intializeSharedMemory()
{
    static int zeroes[3] = {0, 0, 0}; 

    int* shmem = (int*)mmap(NULL, sizeof(int) * 3, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    memcpy(shmem, zeroes, sizeof(zeroes));

    return shmem;
}

//Calculate precisely the time between two timespec objects
double getElapsedTime(struct timespec start, struct timespec end)
{
    double elapsed = (end.tv_sec - start.tv_sec) * 1000000.0;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000.0;

    return elapsed;
}