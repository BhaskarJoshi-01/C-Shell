#include "../headerfile.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

struct stat filestat;
struct tm *filetime;

void get_print_info(char *filename, char *file)
{
    char type;
    type = ' ';
    stat(filename, &filestat);
    if (S_ISREG(filestat.st_mode))
        type = '-';
    else if (S_ISSOCK(filestat.st_mode))
        type = 's';
    else if (S_ISDIR(filestat.st_mode))
        type = 'd';
    else if (S_ISBLK(filestat.st_mode))
        type = 'b';
    else if (S_ISCHR(filestat.st_mode))
        type = 'c';
    else if (S_ISLNK(filestat.st_mode))
        type = 'l';

    printf("%c", type);

    if (filestat.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if (filestat.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if (filestat.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");
    if (filestat.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if (filestat.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if (filestat.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");
    if (filestat.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if (filestat.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if (filestat.st_mode & S_IXOTH)
        printf("x");
    else
        printf("-");

    printf(" ");
    printf("%3ld", filestat.st_nlink);
    printf(" ");
    printf("%13s", getpwuid(filestat.st_uid)->pw_name);
    printf(" ");
    printf("%13s", getgrgid(filestat.st_gid)->gr_name);
    printf(" ");
    printf("%9ld", filestat.st_size);
    printf(" ");

    filetime = localtime(&(filestat.st_mtime));
    char datestring[250];
    strftime(datestring, sizeof(datestring), "%b %2d %H:%M ", filetime);
    printf("%s", datestring);
    printf(" ");
    int no;
    no = 0;
    if (S_ISDIR(filestat.st_mode))
        blue();
    else if (S_IXUSR & filestat.st_mode)
        green();
    else
        no = 1;
    printf("%s\n", file);
    if (no == 0)
        reset();
}

int filter(const struct dirent *list)
{
    int rval;
    if (list->d_name[0] == '.')
        rval = 0;
    else
        rval = 1;
    return rval;
}

void ls(char **cmdarg)
{
    int flag;
    int aflag;
    int dirnamflag;
    int k, i;
    int lflag = 0;
    flag = 0, aflag = 0;
    dirnamflag = 0;
    int tocheck = 1;
    struct dirent direntry;
    struct dirent **list;
    char directory[4096];
    i = 1;
    while (cmdarg[i] != NULL)
    {
        if (!strcmp(cmdarg[i], "-l"))
        {
            lflag += 1;
        }
        else if (!strcmp(cmdarg[i], "-la"))
        {
            aflag += 1;
            lflag += 1;
        }
        else if (!strcmp(cmdarg[i], "-al"))
        {
            aflag += 1;
            lflag += 1;
        }
        else if (!strcmp(cmdarg[i], "-a"))
        {
            aflag += 1;
        }
        else if (cmdarg[i][0] != '-')
        {
            dirnamflag += 1;
        }
        i += 1;
    }

    if (!lflag)
    {
        if (!dirnamflag)
        {
            if (!aflag)
                k = scandir(".", &list, filter, alphasort);
            else
                k = scandir(".", &list, NULL, alphasort);

            int count;
            count = 0;
            if (k >= 0)
            {
                while (k > count)
                {
                    int no = 0;
                    stat(list[count]->d_name, &filestat);
                    if (S_ISDIR(filestat.st_mode))
                        blue();
                    else if (filestat.st_mode & S_IXUSR)
                        green();
                    else
                        no = 1;
                    printf("%s", list[count]->d_name);
                    printf("\n");

                    if (!no)
                        reset();
                    free(list[count]);
                    count += 1;
                }
                free(list);
                exst = 0;
            }
            else
            {
                perror("ls directory ");
                exst = 1;
                return;
            }
        }
        else
        {
            int j;
            j = 1;
            int flaag = 0;
            while (cmdarg[j] != NULL)
            {
                if (cmdarg[j][0] != '-')
                {
                    char temp[150];

                    if (cmdarg[j][0] == '~')
                    {
                        strcpy(temp, home);
                        strcat(temp, 1 + cmdarg[j]);
                    }
                    else
                        strcpy(temp, cmdarg[j]);

                    if (temp[0] != '-' && (aflag == 0))
                    {
                        k = scandir(temp, &list, filter, alphasort);
                    }
                    else if (temp[0] != '-' && (aflag != 0))
                    {
                        k = scandir(temp, &list, NULL, alphasort);
                    }
                    int count;
                    count = 0;

                    if (k >= 0)
                    {
                        while (k > count)
                        {
                            int no = 0;
                            char filepath1[4096];
                            strcpy(filepath1, temp);
                            strcat(filepath1, "/"), strcat(filepath1, list[count]->d_name);
                            stat(filepath1, &filestat);
                            if (S_ISDIR(filestat.st_mode))
                                blue();
                            else if (S_IXUSR & filestat.st_mode)
                                green();
                            else
                                no = 1;
                            printf("%s", list[count]->d_name);
                            printf("\n");
                            if (!no)
                                reset();
                            free(list[count]);
                            count += 1;
                        }
                        free(list);
                    }
                    else
                    {
                        perror("ls directory ");
                        flaag++;
                        j++;
                        continue;
                    }
                }
                j++;
                printf("\n");
            }
            if (flaag == 0)
            {
                exst = 0;
            }
            else
            {
                exst = 1;
            }
        }
    }
    else //lflag!=0
    {
        {
            if (!dirnamflag)
            {
                if (!aflag)
                    k = scandir(".", &list, filter, alphasort);
                else if (aflag)
                    k = scandir(".", &list, NULL, alphasort);

                if (k >= 0)
                {
                    int count;
                    int total;
                    count = 0, total = 0;
                    while (k > count)
                    {
                        stat(list[count]->d_name, &filestat);
                        total = filestat.st_blocks + total;
                        count += 1;
                    }
                    count = 0;
                    printf("Total %d", total >> 1);
                    printf("\n");
                    while (k > count)
                    {
                        total = filestat.st_blocks + total;
                        get_print_info(list[count]->d_name, list[count]->d_name);
                        count += 1;
                    }
                    free(list);
                    exst = 0;
                }
                if (k < 0)
                {
                    perror("ls directory ");
                    exst = 1;
                    return;
                }
            }
            else
            {
                int j;
                j = 1;
                int flaag = 0;
                while (cmdarg[j] != NULL)
                {
                    if (cmdarg[j][0] != '-')
                    {
                        char temp[150];

                        if (cmdarg[j][0] == '~')
                        {
                            strcpy(temp, home);
                            strcat(temp, 1 + cmdarg[j]);
                        }
                        else
                            strcpy(temp, cmdarg[j]);

                        if (temp[0] != '-' && (aflag == 0))
                        {
                            k = scandir(temp, &list, filter, alphasort);
                        }
                        else if (temp[0] != '-' && (aflag != 0))
                        {
                            k = scandir(temp, &list, NULL, alphasort);
                        }
                        if (k < 0)
                        {
                            perror("ls directory ");
                            flaag++;
                            j++;
                            continue;
                        }
                        else
                        {
                            int count;
                            int total;
                            count = 0, total = 0;
                            char filepath[4096];
                            while (k > count)
                            {
                                strcpy(filepath, temp);
                                strcat(filepath, "/");
                                strcat(filepath, list[count]->d_name);
                                stat(filepath, &filestat);
                                total = filestat.st_blocks + total;
                                count += 1;
                            }
                            count = 0;
                            printf("Total %d\n", total >> 1);
                            char filepath1[4096];
                            while (k > count)
                            {
                                strcpy(filepath1, temp), strcat(filepath1, "/");
                                strcat(filepath1, list[count]->d_name);
                                get_print_info(filepath1, list[count]->d_name);
                                count += 1;
                                free(list[count - 1]);
                            }
                            free(list);
                        }
                    }
                    j++;
                    printf("\n");
                }
                if (!flaag)
                {
                    exst = 0;
                }
                else
                {
                    exst = 1;
                }
            }
        }
    }
}
