#include "shell.h"

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
