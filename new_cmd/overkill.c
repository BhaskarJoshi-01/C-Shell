#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

#include "../headerfile.h"
void killemall(char **args)
{
    if (args[1] != NULL)
    {
        printf(" Too many arguments passed");
        printf("\n");
        exst = 1;
        return;
    }

    int i = 0;
    while (i < backpointer)
    {
        {
            kill(backarray[i].pid, 9);
            backarray[i].status = 0;
        }
        i++;
    }
    backpointer = 0;
    exst = 0;
}
