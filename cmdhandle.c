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

    if (NULL == cmdarray)
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
    // if (!ff)
    //     return NULL;
    return cmdarray;
}
int checkand(char **);

char **splitargs(char *command)
{

    char **argarray = malloc(sizeof(char *) * 105);
    if (NULL == argarray)
    {
        printf("malloc Fails");
        printf("\n");
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
                printf("realloc fails");
                printf("\n");
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
    else
    {
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

    cmdlist[0][0] = 'l';
    cmdlist[0][1] = 's';

    cmdlist[1][0] = 'p';
    cmdlist[1][1] = 'w';
    cmdlist[1][2] = 'd';

    cmdlist[2][0] = 'c';
    cmdlist[2][1] = 'd';

    cmdlist[3][0] = 'e';
    cmdlist[3][1] = 'c';
    cmdlist[3][2] = 'h';
    cmdlist[3][3] = 'o';

    cmdlist[4][0] = 'p';
    cmdlist[4][1] = 'i';
    cmdlist[4][2] = 'n';
    cmdlist[4][3] = 'f';
    cmdlist[4][4] = 'o';

    cmdlist[5][0] = 'h';
    cmdlist[5][1] = 'i';
    cmdlist[5][2] = 's';
    cmdlist[5][3] = 't';
    cmdlist[5][4] = 'o';
    cmdlist[5][5] = 'r';
    cmdlist[5][6] = 'y';

    cmdlist[6][0] = 'n';
    cmdlist[6][1] = 'i';
    cmdlist[6][2] = 'g';
    cmdlist[6][3] = 'h';
    cmdlist[6][4] = 't';
    cmdlist[6][5] = 's';
    cmdlist[6][6] = 'w';
    cmdlist[6][7] = 'a';
    cmdlist[6][8] = 't';
    cmdlist[6][9] = 'c';
    cmdlist[6][10] = 'h';

    cmdlist[7][0] = 's';
    cmdlist[7][1] = 'e';
    cmdlist[7][2] = 't';
    cmdlist[7][3] = 'e';
    cmdlist[7][4] = 'n';
    cmdlist[7][5] = 'v';

    cmdlist[8][0] = 'u';
    cmdlist[8][1] = 'n';
    cmdlist[8][2] = 's';
    cmdlist[8][3] = 'e';
    cmdlist[8][4] = 't';
    cmdlist[8][5] = 'e';
    cmdlist[8][6] = 'n';
    cmdlist[8][7] = 'v';

    cmdlist[9][0] = 'b';
    cmdlist[9][1] = 'g';

    cmdlist[10][0] = 'j';
    cmdlist[10][1] = 'o';
    cmdlist[10][2] = 'b';
    cmdlist[10][3] = 's';

    cmdlist[11][0] = 'o';
    cmdlist[11][1] = 'v';
    cmdlist[11][2] = 'e';
    cmdlist[11][3] = 'r';
    cmdlist[11][4] = 'k';
    cmdlist[11][5] = 'i';
    cmdlist[11][6] = 'l';
    cmdlist[11][7] = 'l';

    cmdlist[12][0] = 'k';
    cmdlist[12][1] = 'j';
    cmdlist[12][2] = 'o';
    cmdlist[12][3] = 'b';

    cmdlist[13][0] = 'f';
    cmdlist[13][1] = 'g';

    char **cmdarray;
    cmdarray = splitcmd(takecommad);
    int i = 0;
    // if (cmdarray[0] == NULL)
    //     return 0;
    // if (strcmp(cmdarray[0], " ") == 0 || strcmp(cmdarray[0], "\t") == 0)
    //     return 0;
    // else
    {
        while (cmdarray[i] != NULL)
        {
            // printf("here comes cmd %s\n", cmdarray[i]);
            execute(cmdarray[i]);
            i++;
        }
    }
}
