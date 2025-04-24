#include "shell.h"

/**
  * _strncmp - Compares at most the first n bytes of str1 and str2
  * @s1: The first string
  * @s2: The second string
  * @len: The limit bytes of comparison
  *
  * Return: int value
  */
int _strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned int pos = 0;
	int diff = 0;

	while (pos < len)
	{
		if (s1[pos] == s2[pos])
		{
			pos++;
			continue;
		}

		else
		{
			diff = s1[pos] - s2[pos];
			break;
		}

		pos++;
	}

	return (diff);
}

/**
 * find_command_path - A better handler for command path
 *
 * @command: The command to search
 * @exit_status: The status for exit (exit code)
 *
 * Return: Tokenized command
 */

char *find_command_path(char *command, int *exit_status)
{
	char *path = _getenv("PATH");
	char *token, *path_copy, *full_path = malloc(BUFFER_SIZE);
	struct stat st;

	if (!full_path)
		return (NULL);

    /* If PATH is NULL or empty, only absolute paths work */
	if (!path || !*path)
	{
		free(full_path);
		*exit_status = 127;
		return (NULL);
	}

	path_copy = strdup(path);
	if (!path_copy)
	{
		free(full_path);
		return (NULL);
	}

	token = strtok(path_copy, ":");
	while (token)
	{
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			free(path);
			return (full_path);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	free(path);
	free(full_path);
	*exit_status = 127;
	return (NULL);
}

/**
 * handle_builtin - Function that handles better the builtins
 *
 * @args: User input
 * @exit_status: Used to handle exit status ($?)
 *
 * Return: 1 if exit, 0 if builtin, -1 if not a builtin
 */

int handle_builtin(char **args, int *exit_status)
{
	builtin_t builtins[] = {
		{"exit", handle_exit},
		{"env", handle_env},
		{"help", handle_help},
		{NULL, NULL}
	};
	size_t i = 0;

	while (builtins[i].name)
	{
		if (_strcmp(args[0], builtins[i].name) == 0)
			return (builtins[i].func(args, exit_status));
		i++;
	}
	return (-1);
}

/**
 * print_error - A function to print errors
 *
 * @args: user input
 * @cmd_c: The number of commands
 * @shell_n: The name of the shell
 * @exit_stat: The exit code
 */

void print_error(char **args, int cmd_c, const char *shell_n, int *exit_stat)
{
	fprintf(stderr, "%s: %d: %s: not found\n", shell_n, cmd_c, args[0]);
	*exit_stat = 127;
}
