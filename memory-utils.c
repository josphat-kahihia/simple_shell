#include "main.h"

/**
 * _realloc - Alternate implementation of realloc
 * @ptr: Pointer to current block
 * @size: Size of block
 *
 * Return: pointer to new block, NULL on error
 */
void *_realloc(void *ptr, size_t size)
{
	char *newptr;
	char *p;
	char *np;

	if (ptr == NULL && size > 0) /* similar to malloc() */
	{
		newptr = malloc(size);
		return (newptr);/* No need to check if == NULL, sends itself*/
	}
	if (ptr != NULL && size == 0) /* similar to calling free() */
	{
		free(ptr);
		return (NULL);
	}
	newptr = malloc(sizeof(char) * size);
	if (newptr == NULL)
		return (NULL);
	p = ptr;
	np = newptr;
	printf("p: %s\n", p);
	while (np <= (newptr + --size))
	{
		*np = *p;
		p++;
		if (!p)
			break;
		np++;
	}
	free(ptr); /* Free old pointer */
	return (newptr);
}
