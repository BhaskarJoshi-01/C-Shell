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
#include "../headerfile.h"
#define bj backarray[jobid]
void checkallkill()
{
    char str[1200];
    int flag;
    flag = 0;
    int i = 0;
    while (i < backpointer)
    {

        sprintf(str, "/proc/%d/status", backarray[i].pid);
        FILE *file = fopen(str, "r");
        if (NULL != file)
        {
            flag += 1;
        }
        i += 1;
    }
    if (!flag)
        backpointer = 0;
}

void jobs(char **args)
{

    checkallkill();
    char str[1200];
    int i = 0;
    if (args[1] != NULL)
    {

        printf("Give Proper arguments: More arguments given");
        printf("\n");
        // printf(":'(");
        exst = 1;
        return;
    }
    while (i < backpointer)
    {
        sprintf(str, "/proc/%d/status", backarray[i].pid);
        FILE *file = fopen(str, "r");

        if (file != NULL)
        {
            int zombflag = 0;

            char bufff[105];
            int count = 0;
            while (fgets(bufff, sizeof(bufff), file))
            {
                count += 1;
                if (count == 2)
                {
                    int icount = 0;
                    while (' ' != bufff[icount])
                    {
                        icount += 1;
                    }
                    while ('\t' == bufff[icount])
                    {
                        icount += 1;
                    }
                    if (('Z' == bufff[(icount - 1)]) && ('S' == bufff[0]))
                    {
                        zombflag += 1;
                    }
                }
                if ((!(count - 3)) && (!zombflag))
                {
                    printf("[%d]", i);
                    printf(" ");
                    printf("\t");
                    int icount;
                    icount = 0;
                    while (bufff[icount] != ' ')
                    {
                        icount += 1;
                    }
                    while ('\t' == bufff[icount])
                    {
                        icount += 1;
                    }
                    if ('T' == bufff[(icount - 1)])
                    {
                        printf("Stopped");
                        printf("\t\t");
                    }
                    else
                    {
                        printf("Running");
                        printf("\t\t");
                    }
                    break;
                }
            }
            if (!zombflag)
            {
                printf("%s", backarray[i].command);
                printf("\t");
                printf("[%d]", backarray[i].pid);
                printf("\n");
            }
            i++;
            zombflag = 0;
        }
        else
            i++;
    }
    // printf(":')");
    exst = 0;
}

void kjobs(char **args)
{
    if (NULL == args[1] || NULL == args[2])
    {
        printf("Give Proper arguments: Less arguments given");
        printf("\n");
        // printf(":'(");
        exst = 1;
    }
    else if (NULL != args[3])
    {
        printf("Give Proper arguments: More arguments given");
        printf("\n");
        // printf(":'(");
        exst = 1;
    }
    else
    {
        int jobnumb;
        jobnumb = atoi(args[1]);
        int signaaal;
        signaaal = atoi(args[2]);
        if (backpointer <= jobnumb)
        {
            printf("Process Does not exists ");
            printf("\n");
            // printf(":'(");
            exst = 1;
        }
        else if (!(backarray[jobnumb].status))
        {
            printf("Process does not exists");
            printf("\n");
            // printf(":'(");
            exst = 1;
        }
        else
        {
            int procnum;
            procnum = backarray[jobnumb].pid;
            printf("%d %d", procnum, signaaal);
            printf("\n");
            // printf(":')");

            if (!(kill(procnum, signaaal) + 1))
            {
                perror("Error in kjobs ");
                // printf(":'(");
                exst = 1;
            }
            else
            {
                // printf(":')");
                exst = 0;
            }
        }
    }
    checkallkill();
    return;
}

void fg(char **args)
{
    pid_t wpid;
    int status;
    if (args[2] != NULL)
    {
        printf("Give Proper arguments: More arguments given");
        printf("\n");
        // printf(":'(");
        exst = 1;
    }
    else
    {

        // printf("");
        int jobid = 0;
        if (args[1] != NULL)
        {
            jobid = atoi(args[1]);
            if (jobid < 0)
            {
                printf("No such job exists\n");
                // printf(":'(");
                exst = 1;
                return;
            }
            else if (jobid >= backpointer)
            {
                printf("No such job exists\n");
                // printf(":'(");
                exst = 1;
                return;
            }
        }
        else
        {
            jobid = backpointer;
            jobid -= 1;
        }

        pid_t y;
        y = getpgrp();

        setpgid(bj.pid, getpgid(0));
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, bj.pid);
        runproc.pid = bj.pid;
        if (kill((bj.pid), SIGCONT) == -1)
        {
            perror("Error in fg");
            // printf(":'(");

            exst = 1;
            return;
        }

        bj.status = 3;
        int useless;
        waitpid(bj.pid, &useless, WUNTRACED);

        tcsetpgrp(STDIN_FILENO, getpgrp());

        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        printf("%d", y);
        printf("\n");
        // printf(":')");
        exst = 0;

        return;
    }
}
