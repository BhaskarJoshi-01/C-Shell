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
#include <limits.h>
#include "../headerfile.h"
char **splitpipe(char *command);
void pipeexec(char **args);

char **splitpipe(char *command)
{

    char **toret = malloc(sizeof(char *) * 105);
    if (NULL == toret)
    {
        printf("malloc Fails");
        exst = 1;
        printf("\n");
    }

    else
    {
        int poi = 0;
        char *token = strtok(command, "|");
        while (token != NULL)
        {
            toret[poi] = token;
            if (poi >= sizeof(toret) / 8)
            {
                toret = realloc(toret, sizeof(char *) * 105);
                if (NULL == toret)
                {
                    printf("realloc fails");
                    exst = 1;
                    printf("\n");
                }
            }
            poi++;
            token = strtok(NULL, "|");
        }

        toret[poi] = 0;
    }

    return toret;
}

void pipeexec(char **args)
{

    char *execmd[100];

    int j, k;
    j = k = 0;

    while (NULL != args[k])
    {
        if (!strcmp(args[k], ">") || !strcmp(args[k], "<") || !strcmp(args[k], ">>"))
        {
            k++;
        }
        else if (k > 0)
        {
            if (strcmp(args[k - 1], ">") != 0 && strcmp(args[k - 1], "<") != 0 && strcmp(args[k - 1], ">>") != 0)
            {
                execmd[j] = args[k];
                j++;
            }
            k++;
        }
        else
        {
            execmd[j] = args[k];
            j++;
            k++;
        }
    }
    execmd[j] = 0;

    int someflag, andflag;
    someflag = 0;
    andflag = checkand(execmd);
    if (strcmp(execmd[0], "quit") != 0 && strcmp(execmd[0], "exit") != 0)
    {
        for (int i = 0; i <= 13; ++i)
        {
            if (strcmp(execmd[0], cmdlist[i]) == 0)
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

void tagpiper(char *args)
{
    exst = 0;
    int stdindup, stdoutdup, poi, lol, p;
    stdindup = dup(STDIN_FILENO);
    stdoutdup = dup(STDOUT_FILENO);
    poi = lol = p = 0;
    char **cmds = splitpipe(args);

    while (cmds[lol])
    {
        lol += 1;
    }
    while (p <= (lol - 1))
    {
        char **args = splitargs(cmds[p]);
        int inpos, outpos, appos;
        inpos = -2, outpos = -3, appos = -4;
        int i = 0;
        while (NULL != args[i])
        {
            if (!strcmp(args[i], "<"))
                inpos = i;
            else if (!strcmp(args[i], ">"))
                outpos = i;
            else if (!strcmp(args[i], ">>"))
                appos = i;
            i++;
        }

        if (inpos > 0)
        {
            int fdin;
            fdin = open(args[inpos + 1], O_RDONLY);
            if (fdin < 0)
            {
                perror(" Error in Redirection ");
                exst = 1;
                return;
            }
            else
                dup2(fdin, STDIN_FILENO);
        }
        if (outpos > 0)
        {
            int fd;
            fd = open(args[outpos + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd == -1)
            {
                perror(" Error in Redirection ");
                exst = 1;
                return;
            }
            else
            {
                dup2(fd, STDOUT_FILENO);
            }
        }

        if (appos > 0)
        {
            int fdapp;
            fdapp = open(args[appos + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fdapp == -1)
            {
                perror(" Error in Redirection ");
                exst = 1;
                return;
            }
            else
                dup2(fdapp, STDOUT_FILENO);
        }
        if (appos > 0 && outpos > 0)
        {
            printf("INVALID : Can't have both >> and > ");
            printf("\n");
            exst=1;
            break;
        }
        int pos1 = lol - 1;
        if (pos1 != p)
        {
            int pipearr[2];
            pipe(pipearr);
            dup2(pipearr[1], STDOUT_FILENO), pipeexec(args);
            dup2(pipearr[0], STDIN_FILENO), dup2(stdoutdup, STDOUT_FILENO);
            close(pipearr[1]);
            ++p;
        }
        else
        {
            pipeexec(args);
            ++p;
        }
    }

    dup2(stdindup, STDIN_FILENO);
    dup2(stdoutdup, STDOUT_FILENO);
    close(stdindup);
    close(stdoutdup);
}
