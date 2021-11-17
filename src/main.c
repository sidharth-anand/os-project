/*
Members:-
Akhil Macherla - 2019A7PS1211H
Yashaswi Yenugu - 2019A7PS1210H
Rahul Vegesna - 2019A7PS1205H
Sidharth Anand -2019A7PS1203H
Aryan Arora - 2019A7PS1204H
Ritvik Upadhyay - 2019A7PS0163H
Ishaan Khushu - 2019A7PS0107H
*/
#include <stdlib.h>
#include "include/app.h"

int main(int argc, char **argv)
{   
    /*
     Main function, accepts cmdline prompts and calls functions
    */
    AppArgs appArgs = appInit(atoi(argv[1]), atof(argv[2]), atoi(argv[3]), argv[4], argv[5], argv[6]);
    appRun(appArgs);
    appDestroy(appArgs);

    exit(EXIT_SUCCESS);
}