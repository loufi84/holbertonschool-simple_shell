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

char *find_command_path(char *command, int *exit_status)
{
	char *path = _getenv("PATH");
	char *token, *full_path = malloc(BUFFER_SIZE);
	struct stat st;

	if (!path || !full_path)
		return (NULL);

	token = strtok(path, ":");
	while (token)
	{
		snprintf(full_path, BUFFER_SIZE, "%s/%s", token, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (full_path);
		token = strtok(NULL, ":");
	}
	free(full_path);
	*exit_status = 127;
	return (NULL);
}

int handle_builtin(char **args, int *exit_status)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1])
			*exit_status = _atoi(args[1]);
		else
			*exit_status = 0;

		/*Tell main to exit*/
		return (1);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		print_env(environ);
		*exit_status = 0;
		return (0);
	}
	return (-1); /*Not a builtin*/
}


void print_error(char **args, int cmd_count, const char *shell_name, int *exit_status)
{
	fprintf(stderr, "%s: %d: %s: not found\n", shell_name, cmd_count, args[0]);
	*exit_status = 127;
}

