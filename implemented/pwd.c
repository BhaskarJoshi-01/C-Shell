#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../headerfile.h"

void pwd()
{
    char currentdir[4096];
    getcwd(currentdir, 4096);
    printf("%s\n", currentdir);
    exst = 0;
    return;
}
