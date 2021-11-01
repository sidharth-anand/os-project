#include <stdlib.h>

#include "include/app.h"

int main()
{
    AppArgs appArgs = appInit();
    appRun(appArgs);
    appDestroy(appArgs);

    exit(EXIT_SUCCESS);
}