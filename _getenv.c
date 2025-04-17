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
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (strdup(&environ[i][len + 1]));
		}

		i++;
	}

	return (NULL);
}
