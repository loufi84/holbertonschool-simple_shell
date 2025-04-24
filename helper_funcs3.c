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
 * expand_buffer - A function that expands the buffer if needed
 *
 * @buf: The buffer to modify
 * @bufsize: The size of the buffer to modify
 * @pos: The position inside the string
 *
 * Return: A pointer to the new buffer
 */

static char *expand_buffer(char *buf, size_t *bufsize, size_t pos)
{
	size_t new_size;
	char *new_buf;

	/* Check if the buffer is sufficient in size */
	if (pos + 1 < *bufsize)
		return (buf);
	new_size = *bufsize ? *bufsize * 2 : INIT_BUF_SIZE; /* 2x size if needed*/
	new_buf = _realloc(buf, *bufsize, new_size);
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	*bufsize = new_size;
	return (new_buf);
}

/**
 * _getline - A function to mimic getline function
 *
 * @lineptr: A pointer to the place to write the line
 * @n: A pointer to the size of the line
 * @fd: The file descriptor to which we read the line
 *
 * Return: The number of bytes read
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	char tmp[MAX_ARGS], *buf = *lineptr;
	size_t bufsize = *n, pos = 0;
	ssize_t bytes_read, i;

	/* The loop to read the user input via read call */
	while (1)
	{
		bytes_read = read(fd, tmp, MAX_ARGS);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			break;
		for (i = 0; i < bytes_read; i++)
		{
			buf = expand_buffer(buf, &bufsize, pos);/*Check if buffer need expansion*/
			if (!buf)
				return (-1);
			buf[pos++] = tmp[i];
			if (tmp[i] == '\n')
			{
				buf[pos] = '\0';
				*lineptr = buf;
				*n = bufsize;
				return (pos);
			}
		}
	}
	if (pos == 0)
	{
		free(buf);
		return (-1);
	}
	buf[pos] = '\0';
	*lineptr = buf;
	*n = bufsize;
	return (pos);
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
	if (new_size > old_size)
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
