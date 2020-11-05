#include "../headerfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <wait.h>

void sigquit(int signum)
{
    printf(" Well Well Well !!! Now just press enter ");
    printf("\n");
}

void sigtstp(int signum)
{
}

void ctrlchnd(int signum)
{
}
