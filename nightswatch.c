#include <termios.h>
#include "headerfile.h"
#include <sys/wait.h>
#include <dirent.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <locale.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <langinfo.h>
#include <sys/ioctl.h>
int keyDown()
{
    struct termios oldat;
    int chb;
    struct termios newat;

    int key;
    key = tcgetattr(STDIN_FILENO, &oldat);
    if (!key)
    {
        newat = oldat;
        newat.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newat), ioctl(STDIN_FILENO, FIONREAD, &chb), tcsetattr(STDIN_FILENO, TCSANOW, &oldat);
        if (chb > 0)
            return 1;
        else
            return 0;
    }
    else
    {
        perror("in keyDown");
        exst = 1;
    }

    return 0;
}

void newborn()
{
    FILE *dirmem;
    char filname[4096];
    strcpy(filname, "/proc/loadavg");
    dirmem = fopen(filname, "r");
    size_t f_siz;
    if (dirmem == NULL)
    {
        printf("Error in opening /proc/loadavg");
        exst = 1;
    }
    else
    {
        char *str, buff[150];
        f_siz = fread(buff, 1, 100, dirmem);
        buff[f_siz] = '\0';
        str = strtok(buff, " ");
        char arra[150];
        while (NULL != str)
        {
            strcpy(arra, str);
            // arra[f_size]='\0';
            strcpy(buff, arra);
            str = strtok(NULL, " ");
        }
        printf("%s", buff);
    }
}

void interrupt()
{
    char filname[4096];
    strcpy(filname, "/proc/interrupts");
    FILE *dirmem = fopen(filname, "r");
    if (dirmem)
    {
        int count;
        char bufff[100];
        count = 0;
        while (fgets(bufff, sizeof(bufff), dirmem))
        {
            count += 1;
            if (count == 5)
            {
                bufff[95] = '\0';
                printf("%s", 6 + bufff);
                printf("\n");
                break;
            }
            if (count == 1)
            {
                bufff[95] = '\0';
                printf("%s", 6 + bufff);
                printf("\n");
            }
          
        }
    }
    else
    {
        exst = 1;
        printf("Error opening interrupt\n");
    }
}

void nightswatch(char **args)
{
    exst = 0;

    int n;


    if ((args[0] == NULL) || (args[1] == NULL) || (args[2] == NULL) || (args[3] == NULL))
    {
        printf("Arguments are incorrect ");
        printf("\n");
        exst = 1;
        return;
    }
    if (strcmp(args[1], "-n"))
    {
        n = 0;
        printf("Arguments are incorrect ");
        printf("\n");
        exst = 1;

        return;
    }
    else
    {
        n = atoi(args[2]);
    }
    if (!n)
    {
        printf("Arguments are incorrect ");
        printf("\n");
        exst = 1;
        return;
    }

    int f;
    f = 2;
    if (!strcmp(args[3], "newborn"))
        f -= 2;
    else if (!strcmp(args[3], "interrupt"))
        f -= 1;
    else
    {
        printf("incorrect arguments\n");
        exst = 1;

        return;
    }

    int intch;
    int prev;

    time_t start = time(NULL);
    prev = 0;
    intch = 0;

    while (1)
    {
        if (((time(NULL) - start) / n) > prev)
        {
            prev += 1;
            if (!f)
                newborn();
            else if (f == 1)
                interrupt();
        }
        intch = keyDown();
        if (keyDown())
        {
            if (getchar() == 'q')
            {
                return;
            }
            else
            {
            }
        }
    }
}