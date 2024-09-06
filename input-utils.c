#include "main.h"

/**
 * realloc_g_buff - _getline util to realloc the buffer
 * @s: Pointer to the buffer
 * @size: Size of the buffer to be
 *
 * Return: The realloc'd buffer
 */
char *realloc_g_buff(char *s, size_t *size)
{
	if (*size < 1024)
		*size = 1024;
	if (s == NULL)
		s = malloc(sizeof(char) * *size);
	else
		s = _realloc(s, *size);
	return (s);
}
