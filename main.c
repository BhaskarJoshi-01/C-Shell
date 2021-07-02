#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include "headerfile.h"

void green() 
{
    printf("\033[1;32m");
}
void blue()
{
    printf("\033[0;34m");
}
void reset()
{
    printf("\033[0m");
}
void getdir();

void print_promt();

int main()
{
    exst = -1;
    backpointer = 0;
    inithist();
    mypid = getpgrp();
    int sz_home = sizeof(home);
    int sz_prevdir = sizeof(prevdir);
    getcwd(home, sz_home);
    getcwd(prevdir, sz_prevdir);
    signal(SIGTSTP, sigtstp);
    signal(SIGQUIT, sigquit);
    signal(SIGINT, ctrlchnd);
    print_promt();
    return 0;
}
void getdir()
{
    char currentdir[4096];
    int sz_curdir = sizeof(currentdir);
    int flag = 1;
    int i = 0;
    char pathexec[4096], temp[4096];
    getcwd(currentdir, sz_curdir);

    if (strlen(home) > strlen(currentdir))
    {
        blue(), printf("%s", currentdir), reset();
    }
    else
    {
        for (i = 0; i < strlen(home); ++i)
        {
            if (home[i] == currentdir[i])
            {
            }
            else
            {
                flag = 0;
                break;
            }
        }
        blue();
        if (!flag)
        {
            printf("%s", currentdir);
        }
        else
        {
            printf("~");
            printf("%s", currentdir + i);
        }
        reset();
    }

    printf(">");
}

void print_promt()
{
    char host[150], username[150];
    // signal(SIGCHLD, backquit);

    while (1)
    {
        getlogin_r(username, 150);
        gethostname(host, 150);
        char *takecommand;
        if (exst == 1)
        {
            printf(":'(");
            exst = 2;
        }
        if (exst == 0)
        {
            printf(":')");
            exst = 2;
        }
        green(), printf("<"), reset();
        green(), printf("%s", username), reset();
        green(), printf("@"), reset();
        green(), printf("%s", host), reset(), printf(":");
        getdir();
        size_t cmdlength;
        cmdlength = 0;
        int ret_val = getline(&takecommand, &cmdlength, stdin);
        if (ret_val == EOF)
        {
            printf("\n");
            break;
        }

        commandexec(takecommand);
    }
}
