#include "shell.h"

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
