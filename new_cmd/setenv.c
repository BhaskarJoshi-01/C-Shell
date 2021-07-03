#include "../headerfile.h"
#include <stdio.h>
#include <stdlib.h>

void seten(char **args)
{
    exst = 0;
    if (!args[1])
    {
        printf("specify variable to set : Provide Correct Arguments");
        printf("\n");
        exst = 1;
    }
    else if ((args[2] != NULL) && (  args[3] != NULL))
    {
        printf("Too many arguments passed");
        printf("\n");
        exst = 1;
    }
    else if (args[2] == NULL)
    {
        if (0 > setenv(args[1], "", 1))
        {
            perror(" ERROR in setenv ");
            exst = 1;
        }
    }
    else
    {
        if (0 > setenv(args[1], args[2], 1))
        {
            perror(" ERROR in setenv ");
            exst = 1;
        }
    }
}

void unseten(char **args)
{

    exst = 0;

    if (args[1] != NULL && args[2] == NULL)
    {
        if (0 > unsetenv(args[1]))
        {
            perror(" ERROR in unsetenv ");
            exst = 1;
        }
    }
    else
    {
        printf(" Input is invalid ");
        printf("\n");
        exst=1;

    }
}
