#include "shell.h"

/**
* path_handling - handles the path if not absolute
* @cmd: an array of tokens (= input)
*
* Return: 0 in success, -1 in failure
*/

int path_handling(char **cmd)
{
	static char buffer[BUFFER_SIZE];
	char **dir;
	char *path_env = getenv("PATH");
	char *full_path = split_string(path_env, dir);/*Look for the path*/
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

	while (full_path)
	{
		sprintf(buffer, "%s", *cmd);

		if (access(buffer, F_OK) && access(buffer, X_OK))
		{
			return (0);
		}

		else
		{
			return (-1);
		}

		i++;
	}

	return (0);
}
