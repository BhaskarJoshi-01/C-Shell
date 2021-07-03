#include "../headerfile.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

int logicalexec(char *cmd);
void logical(char *cmd)
{
    int arr[2000], i, j, val, operator_number;
    memset(arr, -1, sizeof(arr));
    i = j = 0;

    char cmdcpy[1500];
    strcpy(cmdcpy, cmd);
    char **execmd;
    execmd = splitargs(cmd);
    while (execmd[j])
    {
        if (!strcmp(execmd[j], "$"))
        {
            arr[i] = 1;
            i++;
        }
        else if (!strcmp(execmd[j], "@"))
        {
            arr[i] = 0;
            i++;
        }
        j++;
    }

    char *token = strtok(cmdcpy, "$@");
    operator_number = i;
    i = 0;
    char *str[250];

    while (NULL != token)
    {
        str[i] = token;
        i++;
        token = strtok(NULL, "$@");
    }
    val = logicalexec(str[0]);
    i = 1;

    while (i < (operator_number + 1))
    {
        int temp_val;
        int cnd1, cnd2, cnd3, cnd4;
        cnd1 = ((strcmp(str[i], "") == 0) ? 1 : 0);
        cnd2 = ((strcmp(str[i], "\t") == 0) ? 1 : 0);
        cnd3 = ((strcmp(str[i], " ") == 0) ? 1 : 0);
        cnd4 = ((strcmp(str[i], "  ") == 0) ? 1 : 0);
        if (arr[i - 1] == 1 && val == 1)
            break;
            
        if (cnd1 || cnd2 || cnd3 || cnd4)
        {
            printf("Syntax is not correct");
            printf("\n");
            return;
        }
        else
        {
            temp_val = logicalexec(str[i]);
        }

       
        if (arr[i - 1] == 1)
        {
            val |= (temp_val);
        }
        if (arr[i - 1] == 0)
        {
            val &= (temp_val);
        }
        i++;
    }
    exst = 1 - val;
}

int logicalexec(char *cmd)
{
    int pipeflag, pipcheck;
    pipcheck = pipeflag = 0;
    char **execmd;
    int someflag;

    char cmdcpy[1200];
    cmdcpy[0] = 0;
    strcpy(cmdcpy, cmd);

    execmd = splitargs(cmd);

    while (NULL != execmd[pipcheck])
    {
        if ((!strcmp(execmd[pipcheck], ">>")) | (!strcmp(execmd[pipcheck], "<")) | (!strcmp(execmd[pipcheck], "|")) | (!strcmp(execmd[pipcheck], ">")))
        {
            tagpiper(cmdcpy);
            pipeflag += 1;
            break;
        }
        pipcheck += 1;
    }

    if (!pipeflag)
    {
        someflag = 0;
        int andflag = checkand(execmd);
        if (strcmp(execmd[0], "quit") != 0 && strcmp(execmd[0], "exit") != 0)
        {
            for (int i = 0; i <= 13; ++i)
            {
                if ((strcmp(execmd[0], cmdlist[i]) == 0))
                {
                    if (i == 0)
                        ls(execmd);
                    if ((i) == 1)
                        pwd();
                    if ((i) == 2)
                        cd(execmd);
                    if ((i) == 3)
                        echo(execmd);
                    if ((i) == 4)
                        pinfo(execmd);
                    if ((i) == 5)
                        history(execmd);
                    if ((i) == 6)
                        nightswatch(execmd);
                    if (i == 7)
                        seten(execmd);
                    if (i == 8)
                        unseten(execmd);
                    if (i == 9)
                        bghand(execmd);
                    if (i == 10)
                        jobs(execmd);
                    if (i == 11)
                        killemall(execmd);
                    if (i == 12)
                        kjobs(execmd);
                    if (i == 13)
                        fg(execmd);
                    someflag += 1;
                }
            }
            if (!someflag)
                unimplemented(execmd, andflag);
        }
        else
        {
            exhis();
            exit(0);
        }

        andflag = 0;
    }
    return 1 - exst;
}