#include "headerfile.h"
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

char **splitcmd(char *takecommand)
{
    char **cmdarray = malloc(sizeof(char *) * 105);
    int pt = 0;

    if (cmdarray == NULL)
    {
        printf("malloc Fails");
        printf("\n");
        exst = 1;
    }
    int ff = 0;
    char *placeholder = strtok(takecommand, ";\n");
    while (placeholder != NULL)
    {
        ff++;
        if (pt >= sizeof(cmdarray) / 8)
        {
            cmdarray = realloc(cmdarray, sizeof(char *) * 105);
            if (NULL == cmdarray)
            {
                printf("realloc fails");
                printf("\n");
                exst = 1;
            }
        }

        cmdarray[pt] = placeholder;
        placeholder = strtok(NULL, ";\n");
        pt++;
    }

    cmdarray[pt] = 0;
    return cmdarray;
}
int checkand(char **);

char **splitargs(char *command)
{

    char **argarray = malloc(sizeof(char *) * 105);
    if (NULL == argarray)
    {
        printf("malloc Fails\n");
        exst = 1;
    }
    char *placeholder = strtok(command, " \t");
    int pt = 0;
    int ff = 0;
    while (placeholder != NULL)
    {
        if (pt >= sizeof(argarray) / 8)
        {
            argarray = realloc(argarray, sizeof(char *) * 105);
            if (NULL == argarray)
            {
                printf("realloc fails\n");
                exst = 1;
            }
        }

        argarray[pt] = placeholder;
        placeholder = strtok(NULL, " ");
        pt++;
    }
    argarray[pt] = 0;
    return argarray;
}
int checkand(char **execmd)
{
    int retflag, i = 1;
    retflag = 0;
    if (execmd[0][strlen(execmd[0]) - 1] == '&')
    {
        retflag += 1;
    }
    else
    {
    }
    while (execmd[i] != NULL)
    {
        if (strcmp(execmd[i], "&") == 0)
        {
            execmd[i] = NULL;
            retflag += 1;
        }
        i++;
    }
    return retflag;
}
int checklogical(char **execmd)
{
    int retflag, i = 1;
    retflag = 0;
    if ((execmd[0][strlen(execmd[0]) - 1] == '@') || (execmd[0][strlen(execmd[0]) - 1] == '$'))
    {
        retflag += 1;
    }
    while (execmd[i] != NULL)
    {
        if (strcmp(execmd[i], "@") == 0)
        {
            execmd[i] = NULL;
            retflag += 1;
        }
        else if (strcmp(execmd[i], "$") == 0)
        {
            execmd[i] = NULL;
            retflag += 1;
        }

        i++;
    }
    return retflag;
}

void execute(char *cmd)
{
    int logicalno = 0;
    if (cmd[0] != '\0' && cmd[0] != ' ')
    {
        addhis(cmd);
    }
    char **execmd;
    int someflag;

    char cmdcpy[1200];
    cmdcpy[0] = 0;
    strcpy(cmdcpy, cmd);

    execmd = splitargs(cmd);
    if (execmd[0] == NULL)
        return;

    int pipeflag, pipcheck;
    pipcheck = pipeflag = 0;

    logicalno = checklogical(execmd);
    if (logicalno >= 1)
    {
        logical(cmdcpy);
        return;
    }
    int cnd1, cnd2, cnd3, cnd4;
    while (NULL != execmd[pipcheck])
    {
        cnd1 = (strcmp(execmd[pipcheck], ">>") == 0 ? 1 : 0);
        cnd2 = (strcmp(execmd[pipcheck], "<") == 0 ? 1 : 0);
        cnd3 = (strcmp(execmd[pipcheck], "|") == 0 ? 1 : 0);
        cnd4 = (strcmp(execmd[pipcheck], ">") == 0 ? 1 : 0);
        if (cnd1 || cnd2 || cnd3 || cnd4)
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
}

char *commandexec(char *takecommad)
{
    strcpy(cmdlist[0],"ls");
    strcpy(cmdlist[1],"pwd");
    strcpy(cmdlist[2],"cd");
    strcpy(cmdlist[3],"echo");
    strcpy(cmdlist[4],"pinfo");
    strcpy(cmdlist[5],"history");
    strcpy(cmdlist[6],"nightswatch");
    strcpy(cmdlist[7],"setenv");
    strcpy(cmdlist[8],"unsetenv");
    strcpy(cmdlist[9],"bg");
    strcpy(cmdlist[10],"jobs");
    strcpy(cmdlist[11],"overkill");
    strcpy(cmdlist[12],"kjobs");
    strcpy(cmdlist[13],"fg");


    char **cmdarray;
    cmdarray = splitcmd(takecommad);
    int i = 0;
    {
        while (cmdarray[i] != NULL)
        {
            execute(cmdarray[i]);
            i++;
        }
    }
}
