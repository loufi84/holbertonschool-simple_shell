#include "shell.h"

/**
* _getenv - gets an environnement variable
* @name: the variable to be found
*
* Return: the content of the environnement variable
*/

char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	while (environ[i] != NULL)
	{/*If name = the name of the variable in environ[i] until sign "="*/
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{/*Return the path after the sign "="*/
			return (strdup(&environ[i][len + 1]));
		}

		i++;
	}

	return (NULL);
}

/**
 * _realloc - Re-allocate a memory block
 * @ptr: The original content of old allocated memory
 * @new_size: The new size of allocated memory
 * @old_size: The old size of memory
 * Return: Nothing
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *new, *old = ptr;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size);/*Allocate new memory block*/
	if (new == NULL)
	{
		return (NULL);
	}
	if (new_size > old_size)/*Copy contents from old to new block*/
	{
		for (i = 0; i < old_size; i++)
		{
			new[i] = old[i];
		}
	}
	else
	{
		for (i = 0; i < new_size; i++)
		{
			new[i] = old[i];
		}
	}
	free(ptr);
	return (new);
}

/**
* comments_handling - handles the comments in the shell
* @line: the comment to be treated
*
* Return: nothing
*/

void comments_handling(char *line)
{
	size_t i = 0;

	if (line == NULL)
	{
		return;
	}

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '#')/*If there's '#', ignore everything behind*/
		{/*Only consider it as a comment if preceded by space or is first char*/
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
	}
}

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
	if (WIFEXITED(status))/*If child exited normally*/
		*exit_stat = WEXITSTATUS(status);/*Get child's exit status*/
	else
		*exit_stat = 1;/*Default to 1 if abnormal exit*/
	free(cmd_path);
}


/**
* _strcmp - compares 2 strings
* @s1: first string to be compared
* @s2: second string to be compared
*
* Return: an integer
*/

int _strcmp(char *s1, char *s2)
{

	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{

		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}

		i++;
	}

	return (s1[i] - s2[i]);

}
