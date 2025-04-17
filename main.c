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
		if (split_string(line, args) == 0)
		{
			free(line);
			continue;
		}
		cmd = split_string(line, args);
		if (what_is_cmd(&cmd) != 0)
		{
			run_cmd(&cmd);
		}
		free(line);
	}
	return (0);
}
