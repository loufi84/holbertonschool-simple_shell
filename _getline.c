#include "shell.h"

static char *expand_buffer(char *buf, size_t *bufsize, size_t pos)
{
	size_t new_size;
	char *new_buf;

	if (pos + 1 < *bufsize)
		return (buf);
	new_size = *bufsize ? *bufsize * 2 : INIT_BUF_SIZE;
	new_buf = realloc(buf, new_size);
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	*bufsize = new_size;
	return (new_buf);
}

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	char tmp[MAX_ARGS], *buf = *lineptr;
	size_t bufsize = *n, pos = 0;
	ssize_t bytes_read, i;

	while (1)
	{
		bytes_read = read(fd, tmp, MAX_ARGS);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			break;
		for (i = 0; i < bytes_read; i++)
		{
			buf = expand_buffer(buf, &bufsize, pos);
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

