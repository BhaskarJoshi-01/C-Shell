#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include "../headerfile.h"

int cd(char **args)
{
    char currdir[250];
    int returnval;
    if (args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "~/") == 0)
    {
        getcwd(currdir, sizeof(currdir));
        strcpy(prevdir, currdir);
        returnval = chdir(home);
    }
    
    else if (strcmp(args[1], "-") != 0 && ( (args[1])!=NULL))
    {
        getcwd(currdir, sizeof(currdir));
        strcpy(prevdir, currdir);
        returnval = chdir(args[1]);
    }

    else if (strcmp(args[1], "-") == 0)
    {
        printf("%s", prevdir);
        printf("\n");
        getcwd(currdir, sizeof(currdir));
        returnval = chdir(prevdir);
        strcpy(prevdir, currdir);
    }

    if (returnval >= 0)
    {
        exst = 0;
        return 0;
    }

    else
    {
        perror("cd");
        exst = 1;
        return -1;
    }
}
