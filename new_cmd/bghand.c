#include <string.h>
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

void bghand(char **args)
{
    int jobid;
    int a, j, cv;
    jobid = cv = 0;
    a = 1;

    if (args[1])
    {
        j = strlen(args[1]);
        while (j)
        {
            jobid += (args[1][j - 1] - '0') * a;
            a *= 10;
            j -= 1;
        }
    }

    while (args[cv])
    {
        cv += 1;
    }

    if ( cv> 2)
    {
        printf(" Too many arguments passed ");
        printf("\n");
        exst = 1;
    }
    else
    {
        if(cv == 1 )
        {
            jobid = backpointer;
            jobid--;
        }
        if ((jobid >= backpointer) || (jobid < 0))
        {
            printf(" No such job exists \n");
            exst = 1;
        }
        else if (backarray[jobid].status != 0)
        {
            if (kill(backarray[jobid].pid, 18) != -1)
            {
                backarray[jobid].status = 1;
                exst = 0;
            }
            else
            {
                perror(" Error in bghand ");
                exst = 1;
            }
        }
        else
        {
            printf(" No such job exists \n");
            exst = 1;
        }
    }
}
