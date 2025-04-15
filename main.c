#include "shell.h"

/**
 * main - Entry point
 *
 * Return: 0 for success, various errors
 */

int main(void)
{
	pid_t pid;
	int status;
	char *line, **args[MAX_ARGS];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("simple_shell> ");
		fflush(stdout);

		line = read_line();
		if (line == NULL)
			break;
		if (split_string(line, args) == 0)
		{
			free(line);
			continue;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			continue;
		}
		if (pid == 0)
		{

		}
		else
			wait(&status);
		free(line);
		free(args);
	}
	return (0);
}
