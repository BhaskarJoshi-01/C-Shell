#include "../headerfile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <stddef.h>

void pinfo(char **args)
{
    int pid;
    char str[1500];

    if (args[1] == NULL)
    {
        pid = getpid();
    }
    else
    {
        if (strcmp(args[1], "&") != 0)
            pid = atoi(args[1]);
        else
            pid = atoi(args[2]);
    }

    int pid_zero = 0; //flag to check pid is zero or not
    if (!pid)
    {
        printf("invalid PID");
        printf("\n");
        pid_zero = 1;
        exst = 1;
        return;
    }

    else
    {
        printf("pid -- %d", pid);
        printf("\n");
        sprintf(str, "/proc/%d/status", pid);
        int count = 1;
        FILE *file = fopen(str, "r");
        if (NULL == file)
        {
            perror("File Opening");
            exst = 1;
            return;
        }
        char bufff[1500];

        while (fgets(bufff, sizeof(bufff), file))
        {
           if (count == 3)
            {
                printf("Process Status -- %.*s\n", 2, bufff + 7);
                break;
            }
            
            count += 1;
        }
        fclose(file);
        /////
        sprintf(str, "/proc/%d/statm", pid);
        file = fopen(str, "r");

        size_t var1;
        if (NULL == file)
        {
            perror("File Opening");
            exst = 1;
            return;
        }

        var1 = fread(bufff, 1, 50, file);
        int poss = (int)var1;
        bufff[poss] = '\0';

        ////
        char *str = strtok(bufff, " ");
        printf("memory -- ");
        long long int valuu = atoi(str);
        printf("%Ld", valuu * 4096);
        printf("\n");
        
        fclose(file);

        char path[1500];
        sprintf(str, "/proc/%d/exe", pid);
        int len = -1;
        len = readlink(str, path, 1499);
        if ((len) == -1)
        {
            perror("Error opening proc/pid/exe file \n");
            exst = 1;
        }
        else
        
        {
            printf("Executable Path -- "), printf("%.*s\n", (int)strlen(home) + 6, path);
            exst = 0;
        } 
        // fclose(file);
    }
}
