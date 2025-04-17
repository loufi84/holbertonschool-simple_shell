#include "shell.h"

/**
* what_is_cmd - check if the command is an absolute path or a built_in
* @cmd: an array of tokens (= input)
*
* Return: 0 in success, -1 in failure
*/

int what_is_cmd(char **cmd)
{
	builtin_t *verif;
	int i = 0;
	char *path_env = getenv("PATH");

	if (cmd == NULL || *cmd == NULL)/*Check if pointers are valid*/
	{
		return (-1);
	}

	while (verif != NULL)
	{/*If cmd is a built-in, call the correct function*/
		if (strcmp(verif[i].name, cmd[0]) == 0)
		{
			verif[i].func;
			return (0);
		}

		i++;
	}

	if (strcmp(cmd[0], "/") == 0)/*Check if cmd is an absolute path*/
	{/*If path exists and if it's executable, execute the input*/
		if (access(path_env, F_OK) && access(path_env, X_OK))
		{
			execve(path_env, cmd, environ);
		}

		else
		{
			return (-1);
		}
	}

	else/*If not a built-in nor an absolute path*/
	{
		return (-1);
	}
}
