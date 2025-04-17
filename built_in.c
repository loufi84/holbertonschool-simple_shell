#include "shell.h"

/**
 * built_in - A function that calls a built_in
 *
 * @cmd: The command to check in the built_in struct
 *
 * Return: 1 if built_in, 0 otherwise
 */

int built_in(char *cmd, char **args)
{
	builtin_t builtins[] = {
	{"exit", shutdown},
	{"env", print_env},
	{"cd", cd_builtin},
	{NULL, NULL}
	};
	int i;

	for (i = 0; builtins[i].name != NULL; i++)
	{
		if (strcmp(cmd, builtins[i].name) == 0)
		{
			builtins[i].func(args);
			return (1);
		}
	}
	return (0);
}
