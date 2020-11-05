#include <signal.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include "headerfile.h"
#define bb backarray[backpointer]

void backquit1(int);

void unimplemented(char **execmd, int checkand)
{
    pid_t proccessid;
    int i;
    proccessid = fork();
    i = 0;
    if (0 > proccessid)
    {
        printf(" Fork error ");
        exst = 1;
    }
    else if (!proccessid)
    {
        setpgid(0, 0);
        {
            int pt;
            pt = execvp(execmd[0], execmd);
            // if(pt==-1)
            // {
            //     exst=1;
            // }
            if (pt == -1)
            {
                perror("could not execute");
                exst = 1; //sad
                // return;
                // printf(":'(");
                exit(EXIT_FAILURE);
            }
            else
            {
                // printf(":')");
                exit(EXIT_SUCCESS);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {

        if (!checkand)
        {

            runproc.pid = proccessid, runproc.index = backpointer, runproc.command = execmd[0];

            signal(SIGTTIN, SIG_IGN), signal(SIGTTOU, SIG_IGN), signal(SIGCHLD, sigtstp);
            tcsetpgrp(0, proccessid);
            waitpid(proccessid, &i, WUNTRACED);
            if (i > 0)
                exst = 1;
            if (i <= 0)
                exst = 0;

            tcsetpgrp(0, getpgid(0));
            signal(SIGTTIN, SIG_DFL), signal(SIGTTOU, SIG_DFL);

            if (WIFSTOPPED(i))
            {
                bb.pid = runproc.pid;
                bb.status = 2;
                exst = 1;
                printf("process %d sent to background ", runproc.pid);
                printf("\n");
                bb.command = "0";
                bb.command = runproc.command;
                backpointer += 1;
                runproc.pid = 0;
            }
        }

        else
        {

            signal(SIGCHLD, backquit);
            bb.status = 1;
            bb.pid = proccessid;
            bb.command = execmd[0];
            bb.index = backpointer;
            backpointer += 1;
            setpgid(proccessid, 0);
            tcsetpgrp(STDIN_FILENO, getpgrp());

            printf("process ");
            printf("%s with pid %d", execmd[0], proccessid);
            printf(" started \n");
            exst = 0;
        }
    }
}

void backquit(int somesig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    if (pid)
    {
        int i = 0;
        while (backpointer > i)
        {
            if (pid == backarray[i].pid)
            {
                if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS))
                {
                    fprintf(stderr, "\033[32m \n %s with pid %d exited normally \n\033[0m", backarray[i].command, pid);
                }
                else if (WIFEXITED(status))
                {
                    fprintf(stderr, "\033[31m \n %s with pid %d exited abnormally \n\033[0m", backarray[i].command, pid);
                }
                i++;
            }
            else
            {
                i++;
            }
        }
    }
    printf("\n");
    fflush(stdout);
}
