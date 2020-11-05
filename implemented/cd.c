#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

#include "../headerfile.h"

#define exchange strcpy(prevdir, currdir)
int cd(char **args)
{
    char hol[250];
    char currdir[250];
    int returnval;
    if (args[1] == NULL)
    {
        getcwd(currdir, sizeof(currdir));
        exchange;
        returnval = chdir(home);
    }
    else if (strcmp(args[1], "~") == 0)
    {
        getcwd(currdir, sizeof(currdir));
        exchange;
        returnval = chdir(home);
    }
    else if (strcmp(args[1], "~/") == 0)
    {
        getcwd(currdir, sizeof(currdir));
        exchange;
        returnval = chdir(home);
    }
    else if (strcmp(args[1], "-") != 0 && (NULL != (args[1])))
    {
        getcwd(currdir, sizeof(currdir));
        exchange;
        returnval = chdir(args[1]);
    }

    else if (strcmp(args[1], "-") == 0)
    {
        printf("%s", prevdir);
        printf("\n");
        getcwd(currdir, sizeof(currdir));
        returnval = chdir(prevdir);
        exchange;
    }

    if (returnval >= 0)
    {
        // printf(":')");
        exst = 0;
        return 0;
    }

    else
    {
        perror("cd");
        // printf(":'(");
        exst = 1;
        return -1;
    }
}
