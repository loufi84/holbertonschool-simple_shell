#include "shell.h"

/**
 * handle_env - Function to handle env command
 *
 * @args: User input
 * @exit_status: The exit code
 *
 * Return: Always 0
 */

int handle_env(char **args, int *exit_status)
{
	(void)args;
	print_env(environ);
	*exit_status = 0;
	return (0);
}

/**
 * handle_help - Function that handle help command
 *
 * @args: User input
 * @exit_status: The exit code
 *
 * Return: Always 0
 */

int handle_help(char **args, int *exit_status)
{
	if (args[1] == NULL)
		shell_help(args);
	else
	{
		if (_strcmp(args[1], "exit") == 0)
			help_exit();
		else if (_strcmp(args[1], "env") == 0)
			help_env();
		else if (_strcmp(args[1], "help") == 0)
			help_help();
		else
			fprintf(stderr, "help: no help topics match %s\n", args[1]);
	}
	*exit_status = 0;
	return (0);
}
