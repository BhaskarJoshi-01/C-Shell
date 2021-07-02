#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headerfile.h"

void echo(char **args)
{
	int n = 0;
	int i = 1;
	if (args[i] == NULL)
	{
		printf("\n");
		exst = 0;
		n=1;
		return;
	}
	else
	{
		while (args[i] != NULL)
		{
			n=0;
			char *str = strtok(args[i], " \t");
			while (NULL != str)
			{
				printf("%s ", str);
				str = strtok(NULL, " \t");
			}
			n++,i++;
		}
		exst = 0;
		printf("\n");

	}
	return;
}
