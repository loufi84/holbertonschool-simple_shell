#include "shell.h"

/**
 * execute_command - Execute a command with fork and execve
 * @cmd_path: Full path to the command
 * @args: Command arguments
 * @shell_n: Shell name
 * @exit_stat: Exit status pointer
 */
void execute_command(char *cmd_path, char **args, const char *shell_n,
int *exit_stat)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		*exit_stat = 1;
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror(shell_n);
		free(cmd_path);
		exit(127); /*Command not found*/
	}

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_stat = WEXITSTATUS(status);
	else
		*exit_stat = 1;
	free(cmd_path);
}
