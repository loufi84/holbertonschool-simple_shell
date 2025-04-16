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

	char *line, *args[MAX_ARGS];

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
			free(line);
			continue;
		}
		if (pid == 0)
		{
			/* exécute la commande*/
			execvp(args[0], args);
			perror("exec failed");
			exit(EXIT_FAILURE);
		}
		else
			wait(&status);

		for (int i = 0; args[i] != NULL; i++)
			free(args[i]);
		free(line);
	}
	return (0);
}
