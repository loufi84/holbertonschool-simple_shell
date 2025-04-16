#include "shell.h"

/**
* is_built_in - definds if the command is a built-in or not
* @cmd: the array of tokens
*
* Return: 0 in success, -1 in failure
*/

int is_built_in(char **cmd) /*cmd = the array of tokens (=input)*/
{
	static char buffer[BUFFER_SIZE];
	char **dir;
	char *path_env = getenv("PATH");
	int full_path = split_string(path_env, dir);/*Look for the path*/
	int i = 0;

	if (cmd == NULL || *cmd == NULL)/*Check if pointers are valid*/
	{
		return (-1);
	}

/*Check if PATH is absent or here but empty*/
	if (path_env == NULL || path_env[0] == '\0')
	{
		return (-1);
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

	else
	{
		while (full_path)
		{
			sprintf(buffer, "%s", *cmd);

			if (access(buffer, F_OK) && access(buffer, X_OK))
			{
				execve(buffer, cmd, environ);
			}

			else
			{
				return (-1);
			}

			i++;
		}
	}

	return (0);
}
