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

	char *line, *args[MAX_ARGS], *cmd;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("simple_shell> ");
		fflush(stdout);

		line = read_line();
		if (line == NULL)
			break;
		if (split_string(line, args) == NULL || args[0] == NULL)
		{
			free(line);
			continue;
		}
		if (what_is_cmd(args) != 0)
		{
			run_cmd(args);
		}
		free(line);
	}
	return (0);
}
