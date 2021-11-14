#include <stdlib.h>

#include "include/app.h"

int main(int argc, char **argv)
{
    AppArgs appArgs = appInit(atoi(argv[1]), atof(argv[2]), atoi(argv[3]), argv[4], argv[5]);
    appRun(appArgs);
    appDestroy(appArgs);

    exit(EXIT_SUCCESS);
}