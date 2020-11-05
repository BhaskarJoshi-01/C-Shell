#include "../headerfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#define mod 20
void addhis(char *cmd)
{
    strcpy(his.history[(his.histins % mod)], cmd);
    his.histins += 1;
}

void history(char **cmd)
{
    exst = 0;
    int n, k, i;
    k = 0, i = 0;

    if (cmd[1] == NULL)
        n = 10;
    else
        n = atoi(cmd[1]);
    if (n > 20)
    {
        n = 20;
    }
    if ((cmd[1] != NULL) && (n == 0))
    {
        if ((strcmp(cmd[1], "0") != 0))
        {
            printf("Provide numeric arguments \n");
            exst = 1;
        }
    }

    for (i = n; i > 0; --i)
    {
        k = his.histins - i;
        k %= mod;
        k += mod;
        k %= mod;
        if ((his.history[k] != NULL) && strlen(his.history[k]))
        {
            printf("%s ", his.history[k]);
            printf("\n");
        }
    }
}

void exhis()
{
    FILE *hfile = fopen(his_path, "wb");
    fwrite(&his, sizeof(struct hist), 1, hfile);
    if (hfile < 0)
        fprintf(stderr, "Error opening file");

    fclose(hfile);
    exit(0);
}

void inithist()
{
    char currentdir[4096];
    getcwd(currentdir, 4096);
    strcat(currentdir, "/.history");
    strcpy(his_path, currentdir);
    FILE *hfile = fopen(his_path, "rb");
    if (hfile != NULL)
    {
        fread(&his, sizeof(struct hist), 1, hfile);
        fclose(hfile);
    }
    else
        his.histed = 0, his.histins = 0;
}
