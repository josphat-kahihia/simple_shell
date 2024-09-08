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

/**
 * _getline_helper - helper fn for getline
 * @lp: The linepointer
 * @i: read pointer
 * @mark: The write pointer
 *
 * Description: This function wraps the assignment of the linepointer,
 * following confirmation of content (either with or without EOF).
 * Was copied verbatim from the function.
 *
 * Return: A pointer to the input string
 */
char *_getline_helper(char **lp, char *i, char *mark)
{
	if (*i == '\n') /* conventional line, ending with \n */
		*lp = get_substring(*lp, i);
	if (*i != '\n' && *mark != '\n') /* EOF with content */
	{
		*lp = get_substring(*lp, mark);
		write(STDOUT_FILENO, "\n", 2);
	}
	return (*lp);
}

/**
 * _getline_setter - helper function for _getline
 * @mark: pointer to write position
 * @i: read pointer
 * @rv: total byte count
 * @br: read()'s byte count
 *
 * Description: This is literally here only to satisfy betty's function length
 * check. It sets the 4 values at the end of the while (br > 0) statement in
 * _getline().
 *
 * Return: rv
 */
ssize_t _getline_setter(char *mark, char *i, ssize_t rv, ssize_t br)
{
	mark++;
	i = mark;
	i++;
	i--;
	rv += br;
	return (rv);
}

