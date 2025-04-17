#include "shell.h"

char *split_path(char *string, char *array[])
{
	int i = 0;
	char *token;

	token = strtok(string, ":");
	while (token && i < MAX_ARGS - 1)
	{
		array[i++] = token;
		token = strtok(NULL, ":");
	}
	array[i] = NULL;
	return (array[0]);
}
